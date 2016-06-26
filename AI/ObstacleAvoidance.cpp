#include "ObstacleAvoidance.h"
#include "Agent.h"
#include "AIWorld.h"

namespace AI
{

ObstacleAvoidance::ObstacleAvoidance(Agent* pAgent, float weight)
	:	SteeringBehavior(pAgent, weight)
{
}

SVector2 ObstacleAvoidance::Update(float deltatime)
{
	// todo: set bounding volume in character load.
	// Get the transformation matrices
	SMatrix33 agentToWorld = mpAgent->GetTransform();
	SMatrix33 worldToAgent(agentToWorld);
	worldToAgent.Inverse();

	SVector2 vel(mpAgent->GetVelocity());
	float maxSpeed(mpAgent->GetMaxSpeed());
	SVector2 pos(mpAgent->GetPosition());
	SVector2 head(mpAgent->GetHeading());

	// Calculate the length of the bounding volume
	const float minBoxLength = mBoundingVolume.max.x * 3.0f;	// temp
	float range = minBoxLength + (vel.Length() / maxSpeed) * minBoxLength;
	
	// Debug draw
	DrawBoundingVolume(range, agentToWorld);

	const float height = mBoundingVolume.GetHeight() * 0.5f;
	SLineSegment xAxis(0.0f, 0.0f, range, 0.0f);
	SVector2 minIntersect(FLT_MAX, FLT_MAX);
	SCircle closestObstacle;

	bool hasObstacles = false;	// If we actually intersect with any of the obstacles

	AIWorld::ObstacleList obstacles = mpAgent->GetAIWorld().GetObstacles();
	ObstacleList::iterator it = obstacles.begin();
	for (it; it != obstacles.end(); ++it)
	{
		SCircle& circle = *it;

		// Check that the obstacle is within range
		if (Intersect(circle, SCircle(pos, range)))
		{
			// Transform the obstacle into the agent's space
			circle.center = worldToAgent.TransformCoord(circle.center);

			// Ignore obstacles behind the agent.
			// Since we're in the agent's local space, anything with a negative x is behind.
			if (circle.center.x > 0.0f)
			{
				// Expand the radius of the obstacle by the height of the bounding volume
				circle.radius += height;
				
				// If distance from x axis to obstacle's position is less than its radius + half the width of the volumebox
				// then there is a potential intersection.
				if (fabs(circle.center.y) < circle.radius)
				{
					// Get the intersection point, but only if it's positive since a negative point means we're
					// already inside the ostacle.
					SVector2 intersect(GetXIntersect(circle, xAxis), 0.0f);
					if (intersect.x < minIntersect.x)
					{
						// This is the closest intersect so far
						minIntersect = intersect;
						closestObstacle = circle;
						hasObstacles = true;
					}
				}
			}
		}
	}

	SVector2 force(0.0f, 0.0f);
	if (hasObstacles)
	{
		// Debug drawing
		SVector2 worldIntersect = agentToWorld.TransformCoord(minIntersect);
		Graphics_DebugCircle(worldIntersect, 10.0f, 0xffff00);	// closest intersect
		SVector2 closestObsWorld = agentToWorld.TransformCoord(closestObstacle.center);
		Graphics_DebugCircle(closestObsWorld, closestObstacle.radius, 0xf0f000);	// expanded radius

		// Multiplier increases the closer the obstacle is to the agent
		float multiplier = 1.0f + (range - minIntersect.x) / range;

		//float lateralForce = (fabs(closestObstacle.center.y) - closestObstacle.radius) + multiplier;
		float lateralForce = (closestObstacle.radius - closestObstacle.center.y) * multiplier;
		//if (closestObstacle.center.y < 0.0f)
		//{
		//	// Below the x axis y is positive (DX), so we need to invert the force
		//	lateralForce *= -1.0f;
		//}
		//float brakeForce = (minIntersect.x - range) * multiplier;

		const float brakeWeight = 0.2f;
		float brakeForce = (closestObstacle.radius - closestObstacle.center.y) * brakeWeight;

		// Bring the force back into world space
		force = agentToWorld.TransformNormal(SVector2(brakeForce, lateralForce));
	}
	return force;
}

void ObstacleAvoidance::DrawBoundingVolume(const float range, SMatrix33& agentToWorld)
{
	SVector2 pos(mpAgent->GetPosition());
	SVector2 head(mpAgent->GetHeading());

	SVector2 min = agentToWorld.TransformCoord(SVector2(mBoundingVolume.max.x, mBoundingVolume.min.y));
	SVector2 max = agentToWorld.TransformCoord(mBoundingVolume.max);
	SVector2 minline = agentToWorld.TransformCoord(SVector2(range, mBoundingVolume.min.y));
	SVector2 maxline = agentToWorld.TransformCoord(SVector2(range, mBoundingVolume.max.y));

	SLineSegment rangeLine(pos, pos + (head * range));
	Graphics_DebugLine(rangeLine, 0xff0000);
	Graphics_DebugLine(min, minline);
	Graphics_DebugLine(max, maxline);

	// Draw bounding box
	SVector2 tl = agentToWorld.TransformCoord(mBoundingVolume.min);
	SVector2 br = agentToWorld.TransformCoord(mBoundingVolume.max);
	SVector2 tr = agentToWorld.TransformCoord(SVector2(mBoundingVolume.max.x, mBoundingVolume.min.y));
	SVector2 bl = agentToWorld.TransformCoord(SVector2(mBoundingVolume.min.x, mBoundingVolume.max.y));
	Graphics_DebugLine(tl, tr, 0xff00ff);	// Top line
	Graphics_DebugLine(tl, bl, 0xff00ff);	// Left
	Graphics_DebugLine(bl, br, 0xff00ff);	// Bottom
	Graphics_DebugLine(br, tr, 0xff00ff);	// Right
}

float ObstacleAvoidance::GetXIntersect(const SCircle& c, const SLineSegment& l)
{
	// x = Cx +/- sqrt(r^2 - Cy^2)
	float sqrtPart = sqrt(c.radius * c.radius - c.center.y * c.center.y);
	float rootX1 = c.center.x + sqrtPart;
	float rootX2 = c.center.x - sqrtPart;

	// Start with the negative root since it will be closer
	float x = rootX2;
	if (x <= 0.0f)
	{
		// Root2 is behind us, so we have to use the second root
		x = rootX1;
	}
	return x;
}

}
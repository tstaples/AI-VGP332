#include "Wander.h"
#include "Agent.h"

namespace AI
{

Wander::Wander(Agent* pAgent, float weight)
	:	SteeringBehavior(pAgent, weight)
	,	mWanderDistance(75.0f)
	,	mWanderRadius(50.0f)
	,	mTarget(1.0f, 1.0f)
{
}

SVector2 Wander::Update(float deltatime)
{
	// Add small displacement
	mTarget += SVector2(RandomFloat(-1.0f, 1.0f) * RandomFloat(5.0f, 10.0f),
						RandomFloat(-1.0f, 1.0f) * RandomFloat(5.0f, 10.0f));

	// Project back on to the circle
	mTarget.Normalize();
	mTarget *= mWanderRadius;

	// Offset by the wander distance
	SVector2 localTarget = mTarget + SVector2(mWanderDistance, 0.0f);

	// Transform the target back into world space
	SMatrix33 transform = mpAgent->GetTransform();
	SVector2 worldTarget = transform.TransformCoord(localTarget);

	// Debug drawing
	SVector2 circlePos(mpAgent->GetPosition() + (mpAgent->GetHeading() * mWanderDistance));
	Graphics_DebugCircle(circlePos, mWanderRadius, 0x00ff00);
	Graphics_DebugCircle(worldTarget, 10.0f, 0xff0000);

	// Not really needed, but meh
	mpAgent->SetDestination(worldTarget);

	SVector2 posToDest = worldTarget - mpAgent->GetPosition();
	SVector2 desiredVel = Normalize(posToDest) * mpAgent->GetMaxSpeed();
	SVector2 force(desiredVel - mpAgent->GetVelocity());

	return force;
}

}
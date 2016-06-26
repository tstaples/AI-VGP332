#include "Arrive.h"
#include "Agent.h"

namespace AI
{

Arrive::Arrive(Agent* pAgent, float weight)
	:	SteeringBehavior(pAgent, weight)
{
}

SVector2 Arrive::Update(float deltatime)
{
	SVector2 posToDest = mpAgent->GetDestination() - mpAgent->GetPosition();
	SVector2 desiredVel = Normalize(posToDest) * mpAgent->GetMaxSpeed();

	const float dist = posToDest.Length();

	//float KE = 0.5f * (mpAgent->GetMass() * mpAgent->GetVelocity().LengthSquared());
	//float stopForce = KE / dist;

	float maxSpeed = mpAgent->GetMaxSpeed();
	//http://gamedev.stackexchange.com/questions/44400/arrive-steering-behavior
	SCircle slowingArea(mpAgent->GetDestination(), maxSpeed);

	// Check if we're in the slowing area.
	if (dist < slowingArea.radius)
	{
		// Scale the desired velocity by how far in the circle we are
		desiredVel *= (dist / slowingArea.radius);
	}

	//Graphics_DebugCircle(slowingArea, 0xffff00);

	SVector2 force(desiredVel - mpAgent->GetVelocity());
	return force;
}

}
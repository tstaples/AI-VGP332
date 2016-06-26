#include "SeekBahavior.h"
#include "Agent.h"

namespace AI
{

SeekBehavior::SeekBehavior(Agent* pAgent, float weight)
	:	SteeringBehavior(pAgent, weight)
{
}

SVector2 SeekBehavior::Update(float deltatime)
{
	SVector2 posToDest = mpAgent->GetDestination() - mpAgent->GetPosition();
	SVector2 desiredVel = Normalize(posToDest) * mpAgent->GetMaxSpeed();
	SVector2 force(desiredVel - mpAgent->GetVelocity());

	Graphics_DebugLine(mpAgent->GetPosition(), mpAgent->GetPosition() + desiredVel, 0xff0000);
	Graphics_DebugLine(mpAgent->GetPosition(), mpAgent->GetPosition() + mpAgent->GetVelocity(), 0x0000ff);
	Graphics_DebugLine(mpAgent->GetPosition(), mpAgent->GetPosition() + force, 0x00ff00);

	return force;
}

}
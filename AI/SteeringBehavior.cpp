#include "SteeringBehavior.h"
#include "Agent.h"

namespace AI
{

SteeringBehavior::SteeringBehavior(Agent* pAgent, float weight)
	:	mpAgent(pAgent)
	,	mWeight(weight)
	,	mActive(false)
{
}

SteeringBehavior::~SteeringBehavior()
{
	mpAgent = nullptr;
}

} // namespace AI
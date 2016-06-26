#include "SteeringModule.h"
#include "Agent.h"
#include "SteeringBehavior.h"

namespace AI
{

SteeringModule::SteeringModule(Agent* agent)
	:	mpAgent(agent)
{
}

SteeringModule::~SteeringModule()
{
	mpAgent = nullptr;
}

SVector2 SteeringModule::Update(float deltaTime)
{
	SVector2 force;
	
	const int numBehaviors = mBehaviors.size();
	for (int i=0; i < numBehaviors; ++i)
	{
		if (mBehaviors[i]->Active())
		{
			// Get the sum of all the forces
			force += mBehaviors[i]->Update(deltaTime) * mBehaviors[i]->GetWeight();
		}
	}

	// Truncate the force to the agent's max force
	force.Truncate(mpAgent->GetMaxForce());

	return force;
}

void SteeringModule::AddBehavior(SteeringBehavior* behavior)
{
	if (behavior)
	{
		behavior->SetActive(true);
		mBehaviors.push_back(behavior);
	}
}

} // namespace AI
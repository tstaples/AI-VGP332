#include "Alignment.h"
#include "Agent.h"
#include "AIWorld.h"

namespace AI
{

Alignment::Alignment(Agent* pAgent, float weight)
	:	SteeringBehavior(pAgent, weight)
	,	mMinDistance(50.0f)
{
}

SVector2 Alignment::Update(float deltatime)
{
	const Agent& myAgent = *mpAgent;
	SVector2 force(0.0f, 0.0f);
	SVector2 pos(mpAgent->GetPosition());
	int neighborInRangeCount = 0;

	// Get all the agents in the world (todo: spatial partition)
	const AIWorld::AgentList& agentlist = mpAgent->GetAIWorld().GetAgents();
	for (auto agent : agentlist)
	{
		if (myAgent.GetID() != agent->GetID())
		{
			force += agent->GetHeading();
			neighborInRangeCount++;
		}
	}

	if (neighborInRangeCount > 0)
	{
		force /= neighborInRangeCount;
	}
	return (force);
}


}
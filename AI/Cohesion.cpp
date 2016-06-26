#include "Cohesion.h"
#include "Agent.h"
#include "AIWorld.h"

namespace AI
{

Cohesion::Cohesion(Agent* pAgent, float weight)
	:	SteeringBehavior(pAgent, weight)
	,	mMinDistance(50.0f)
{
}

SVector2 Cohesion::Update(float deltatime)
{
	const Agent& myAgent = *mpAgent;
	SVector2 force(0.0f, 0.0f);
	SVector2 pos(mpAgent->GetPosition());

	// Get all the agents in the world (todo: spatial partition)
	const AIWorld::AgentList& agentlist = mpAgent->GetAIWorld().GetAgents();
	for (auto agent : agentlist)
	{
		if (myAgent.GetID() != agent->GetID())
		{
			force += agent->GetPosition();
		}
	}

	const int sz = agentlist.size();
	if (sz > 1)	// exclude self
	{
		force /= sz;
	}

	Graphics_DebugLine(pos, force, 0xF5C200);
	return (Normalize(force));
}


}
#include "Separate.h"
#include "Agent.h"
#include "AIWorld.h"

namespace AI
{

Separate::Separate(Agent* pAgent, float weight)
	:	SteeringBehavior(pAgent, weight)
	,	mMinDistance(50.0f)
{
}

SVector2 Separate::Update(float deltatime)
{
	const Agent& myAgent = *mpAgent;
	SVector2 force(0.0f, 0.0f);
	SVector2 pos(mpAgent->GetPosition());
	SCircle myposCircle(pos, mMinDistance);
	const float mindistsq = mMinDistance * mMinDistance;
	
	Graphics_DebugCircle(pos, mMinDistance, 0xFF0000);

	int neighborInRangeCount = 0;

	// Get all the agents in the world (todo: spatial partition)
	const AIWorld::AgentList& agentlist = mpAgent->GetAIWorld().GetAgents();
	AIWorld::AgentList::const_iterator it = agentlist.begin();
	for (it; it != agentlist.end(); ++it)
	{
		if (myAgent.GetID() != (*it)->GetID())
		{
			const SVector2& otherpos = (*it)->GetPosition();
			if (Intersect(myposCircle, SCircle(otherpos, mMinDistance)))
			{
				SVector2 dist(pos - otherpos);
				SVector2 dir(Normalize(dist));
				float d = Max(0.0f, 1.0f - (Length(dist) / mMinDistance));
				dir *= (d * 100.0f);
				force += dir;
				neighborInRangeCount++;
			}
		}
	}

	if (neighborInRangeCount > 1)
	{
		force /= neighborInRangeCount;
	}

	Graphics_DebugLine(pos, pos + force, 0xF5C200);
	return (force);
}


}
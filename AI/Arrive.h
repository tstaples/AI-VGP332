#ifndef INCLUDED_AI_ARRIVE_H
#define INCLUDED_AI_ARRIVE_H

#include "SteeringBehavior.h"

namespace AI
{
class Agent;

class Arrive : public SteeringBehavior
{
public:
	Arrive(Agent* pAgent, float weight);
	virtual ~Arrive() {}

	// Inherited from SteeringBehavior
	virtual SVector2 Update(float deltatime);
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_ARRIVE_H
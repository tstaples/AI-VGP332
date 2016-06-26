#ifndef INCLUDED_AI_COHESION_H
#define INCLUDED_AI_COHESION_H

#include "SteeringBehavior.h"

namespace AI
{
class Agent;

class Cohesion : public SteeringBehavior
{
public:
	Cohesion(Agent* pAgent, float weight);
	virtual ~Cohesion() {}

	// Inherited from SteeringBehavior
	virtual SVector2 Update(float deltatime);

	float mMinDistance;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_COHESION_H
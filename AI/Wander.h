#ifndef INCLUDED_AI_WANDER_H
#define INCLUDED_AI_WANDER_H

#include "SteeringBehavior.h"

namespace AI
{
class Agent;

class Wander : public SteeringBehavior
{
public:
	Wander(Agent* pAgent, float weight);
	virtual ~Wander() {}

	// Inherited from SteeringBehavior
	virtual SVector2 Update(float deltatime);

	float mWanderDistance;
	float mWanderRadius;
	SVector2 mTarget;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_WANDER_H
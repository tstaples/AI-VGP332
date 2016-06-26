#ifndef INCLUDED_AI_SEPARATE_H
#define INCLUDED_AI_SEPARATE_H

#include "SteeringBehavior.h"

namespace AI
{
class Agent;

class Separate : public SteeringBehavior
{
public:
	Separate(Agent* pAgent, float weight);
	virtual ~Separate() {}

	// Inherited from SteeringBehavior
	virtual SVector2 Update(float deltatime);

	float mMinDistance;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_SEPARATE_H
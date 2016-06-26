#ifndef INCLUDED_AI_ALIGNMENT_H
#define INCLUDED_AI_ALIGNMENT_H

#include "SteeringBehavior.h"

namespace AI
{
class Agent;

class Alignment : public SteeringBehavior
{
public:
	Alignment(Agent* pAgent, float weight);
	virtual ~Alignment() {}

	// Inherited from SteeringBehavior
	virtual SVector2 Update(float deltatime);

	float mMinDistance;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_ALIGNMENT_H
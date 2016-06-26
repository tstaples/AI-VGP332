#ifndef INCLUDED_AI_SEEKBEHAVIOR_H
#define INCLUDED_AI_SEEKBEHAVIOR_H

#include "SteeringBehavior.h"

namespace AI
{
class Agent;

class SeekBehavior : public SteeringBehavior
{
public:
	SeekBehavior(Agent* pAgent, float weight);
	virtual ~SeekBehavior() {}

	// Inherited from SteeringBehavior
	virtual SVector2 Update(float deltatime);

};

} // namespace AI

#endif // #ifndef INCLUDED_AI_SEEKBEHAVIOR_H
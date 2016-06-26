#ifndef INCLUDED_AI_STEERINGMODULE_H
#define INCLUDED_AI_STEERINGMODULE_H

#include <vector>
#include <SGE/SGE.h>
using namespace SGE;

namespace AI
{

class Agent;
class SteeringBehavior;

class SteeringModule
{
	typedef std::vector<SteeringBehavior*> SteeringBehaviors;
public:
	SteeringModule(Agent* agent);
	~SteeringModule();

	SVector2 Update(float deltaTime);
	void AddBehavior(SteeringBehavior* behavior);

private:
	Agent* mpAgent;					// Owner
	SteeringBehaviors mBehaviors;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_STEERINGMODULE_H
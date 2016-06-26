#ifndef INCLUDED_AI_STEERINGBEHAVIOR_H
#define INCLUDED_AI_STEERINGBEHAVIOR_H

#include <SGE/SGE.h>
using namespace SGE;

namespace AI
{

class Agent;

class SteeringBehavior
{
public:
	SteeringBehavior(Agent* pAgent, float weight);
	virtual ~SteeringBehavior();

	virtual SVector2 Update(float deltatime) = 0;
	void SetWeight(float w) { mWeight = w; }
	float GetWeight() const { return mWeight; }

	inline bool Active() const { return mActive; }
	inline void SetActive(bool state) { mActive = state; }

protected:
	Agent* mpAgent;
	float mWeight;
	bool mActive;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_STEERINGBEHAVIOR_H
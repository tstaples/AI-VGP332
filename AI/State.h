#ifndef INCLUDED_AI_STATE_H
#define INCLUDED_AI_STATE_H

namespace AI
{

template<typename EntityType>
class State
{
public:
	inline State() {}
	inline virtual ~State() {}

	virtual void Update(EntityType& owner) = 0;
	virtual void Enter(EntityType& owner) = 0;
	virtual void Exit(EntityType& owner) = 0;
};

} // namespace AI

#endif // #ifndef INCLUDED_AI_STATE_H
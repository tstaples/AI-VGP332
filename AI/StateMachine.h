#ifndef INCLUDED_AI_STATEMACHINE_H
#define INCLUDED_AI_STATEMACHINE_H

#include "State.h"
#include <vector>
#include <memory>

namespace AI
{

template<typename T>
class StateMachine
{
	//typedef std::unique_ptr<State<T>> StatePtr;
	//typedef std::vector<StatePtr> StateList;
	typedef State<T>* StatePtr;
	typedef std::vector<StatePtr> StateList;
public:
	StateMachine(T& owner);
	~StateMachine();

	void AddState(State<T>* state);
	void Clear();

	void Update();
	void ChangeState(int stateIndex);

private:
	T& mOwner;
	//StatePtr mpCurrentState;
	StatePtr mpCurrentState;
	StateList mStateList;
};

// StateMachine definitions
#include "StateMachine.inl"

} // namespace AI

#endif // #ifndef INCLUDED_AI_STATEMACHINE_H
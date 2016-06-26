//namespace AI
//{

template<typename T>
StateMachine<T>::StateMachine(T& owner)
	:	mOwner(owner)
	,	mpCurrentState(nullptr)
{
}

template<typename T>
StateMachine<T>::~StateMachine()
{
	Clear();
}

template<typename T>
void StateMachine<T>::AddState(State<T>* state)
{
	//StatePtr stateptr(std::move(state));
	mStateList.push_back(state);
}

template<typename T>
void StateMachine<T>::Clear()
{
	//mpCurrentState.release();
	mpCurrentState = nullptr;
	const int sz = mStateList.size();
	for (int i=0; i < sz; ++i)
	{
		//mStateList[i].release();
		delete mStateList[i];
	}
	mStateList.clear();
}

template<typename T>
void StateMachine<T>::Update()
{
	if (mpCurrentState)
	{
		mpCurrentState->Update(mOwner);
	}
}

template<typename T>
void StateMachine<T>::ChangeState(int stateIndex)
{
	if (mpCurrentState)
	{
		mpCurrentState->Exit(mOwner);
	}

	mpCurrentState = mStateList.at(stateIndex);

	if (mpCurrentState)
	{
		mpCurrentState->Enter(mOwner);
		//mpCurrentState.reset(mStateList.at(stateIndex));
	}
}

//} // namespace AI
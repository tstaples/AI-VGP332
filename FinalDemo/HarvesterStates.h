#ifndef INCLUDED_IDLESTATE_H
#define INCLUDED_IDLESTATE_H

#include <AI/AI.h>
#include "Harvester.h"

// Todo: move to separate files

// Search for mineral locations
// Once location is found, goto movestate
class IdleState : public AI::State<Harvester>
{
public:
	virtual void Update(Harvester& owner);
	virtual void Enter(Harvester& owner);
	virtual void Exit(Harvester& owner);
};

// Move to mineral location
// Once there, goto collect state
class MoveState : public AI::State<Harvester>
{
public:
	virtual void Update(Harvester& owner);
	virtual void Enter(Harvester& owner);
	virtual void Exit(Harvester& owner);
};

// move around slightly in mineral location, held resource count increases
// Once at resource capacity, goto deposit state
class CollectState : public AI::State<Harvester>
{
public:
	virtual void Update(Harvester& owner);
	virtual void Enter(Harvester& owner);
	virtual void Exit(Harvester& owner);
};

// Held resources is set to 0, refinery/global resource count++
// Goto idle
class DepositState : public AI::State<Harvester>
{
public:
	virtual void Update(Harvester& owner);
	virtual void Enter(Harvester& owner);
	virtual void Exit(Harvester& owner);
};

#endif // #ifndef INCLUDED_IDLESTATE_H
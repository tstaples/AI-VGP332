#ifndef INCLUDED_HARVESTER_H
#define INCLUDED_HARVESTER_H

#include <vector>
#include <AI/AI.h>
#include <SGE/SGE.h>
using namespace SGE;

#include "Resource.h"
#include "Refinery.h"

enum HarvesterState
{
	Idle,
	Move,
	Collect,
	Deposit
};

// Used for debug printing
static const char* HarvesterStateNames[4] =
{
	"Idle",
	"Move",
	"Collect",
	"Deposit"
};

class Harvester : public AI::Agent
{
public:
	Harvester(AI::AIWorld& world, int resourceLimit, Refinery& refinery);
	virtual ~Harvester();

	void Load();
	void Unload();
	void Update(float deltatime);
	void Render();

	void ChangeState(HarvesterState state);
	void SetArrive(bool onOff);

private:
	void UpdatePosition(float deltatime);
	void CheckBounds();

public:
	SGE_Sprite mSprite;

	AI::StateMachine<Harvester> mStateMachine;
	AI::SteeringModule mSteeringModule;
	AI::Arrive mArrive;

	Refinery& mRefinery;
	const int mResourceLimit;	// max resources this unit can hold before it needs to deposit
	int mResources;
	Resource* mDestResource;

	HarvesterState mCurrentState;	// used for debug
};

#endif
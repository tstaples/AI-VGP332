#ifndef INCLUDED_REFINERY_H
#define INCLUDED_REFINERY_H

#include <vector>
#include <AI/AI.h>
#include <SGE/SGE.h>
using namespace SGE;

#include "Resource.h"

class Refinery : public AI::Entity
{
public:
	static const char* kName;

	Refinery(AI::AIWorld& world);
	virtual ~Refinery();

	void Load();
	void Unload();
	void Update(float deltatime);
	void Render();

	void Deposit(int numResources) { mResources += numResources; } // add to our resource count
	SVector2 GetEntrance() const;

public:
	SGE_Sprite mSprite;

	int mResources;
};

#endif
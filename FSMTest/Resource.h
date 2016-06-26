#ifndef INCLUDED_RESOURCE_H
#define INCLUDED_RESOURCE_H

#include <AI/AI.h>
#include <SGE/SGE.h>
using namespace SGE;

class Resource : public AI::Entity
{
public:
	static int kResourceCount;	// Used as temp ID's
	static const char* kName;
	
	Resource(AI::AIWorld& aiworld, int resourceCount);

	void Load();
	void Unload();
	void Update(float deltatime);
	void Render();

	void Spawn(const SVector2& pos);
	void SetResourceCount(int count)	{ mResourceCount = count; }
	int ResourceCount() const			{ return mResourceCount; }
	int Gather();
	bool IsActive();

	const SVector2& GetPosition() const { return mPosition; }

private:
	SGE_Sprite mSprite;
	bool mActive;
	int mResourceCount;
};

#endif
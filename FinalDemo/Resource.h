#ifndef INCLUDED_DEMO_RESOURCE_H
#define INCLUDED_DEMO_RESOURCE_H

#include <AI/AI.h>
#include <SGE/SGE.h>

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

	const SGE::SVector2& GetPosition() const { return mPosition; }

private:
	SGE::SGE_Sprite mSprite;
	bool mActive;
	int mResourceCount;
};

#endif
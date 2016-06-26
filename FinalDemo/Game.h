#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <AI/AI.h>
#include <SGE/SGE.h>

#include "Harvester.h"
//#include "Resource.h"
#include "Refinery.h"

class Game
{
	typedef std::vector<class Resource*> Resources;
	//typedef std::vector<std::shared_ptr<Resource>> Resources;
public:
	Game();
	~Game();

	void Load();
	void Unload();
	void Update(float deltatime);
	void Render();

	void InitResources();
	void GenerateResources();

private:
	int mEntityCount;

	AI::AIWorld mAIworld;
	SGE::SGE_Cursor mCursor;
	Resources mResources;
	Harvester mHavester;
	Refinery mRefinery;
};

#endif
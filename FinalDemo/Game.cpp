#include "Game.h"
#include "Resource.h"

#define MAX_RESOUCRES 3
#define RESOURCE_LIMIT 10

Game::Game()
	:	mRefinery(mAIworld)
	,	mHavester(mAIworld, RESOURCE_LIMIT, mRefinery)
	,	mEntityCount(0)
	,	mAIworld(32)
{
}

Game::~Game()
{
}

void Game::Load()
{
	mCursor.Load("carrot.png");
	mHavester.Load();
	mRefinery.Load();

	// Allocate and load (not spawned)
	InitResources();

	mAIworld.AddEntity(&mRefinery);
	mAIworld.RegisterAgent(&mHavester);
}
// ------------------------------------------------------------------------

void Game::Unload()
{
	for (auto res : mResources)
	{
		res->Unload();
		//res.reset();
	}
	mResources.clear();

	mRefinery.Unload();
	mHavester.Unload();
	mCursor.Unload();
	mAIworld.Clear();
	mAIworld.ClearAgents();
}
// ------------------------------------------------------------------------

void Game::Update(float deltatime)
{
	if (Input_IsKeyPressed(Keys::SPACE))
	{
		// Spawn the resources in new positions and reset their resource count
		GenerateResources();
	}

	for (auto res : mResources)
	{
		res->Update(deltatime);
	}

	mRefinery.Update(deltatime);
	mHavester.Update(deltatime);
	mCursor.Update(deltatime);
}
// ------------------------------------------------------------------------

void Game::Render()
{
	for (auto res : mResources)
	{
		res->Render();
	}

	mAIworld.Render();
	mRefinery.Render();
	mHavester.Render();
	mCursor.Render();
}

void Game::InitResources()
{
	for (int i=0; i < MAX_RESOUCRES; ++i)
	{
		int resourceCount = RandomInt(5, 15);
		//Resource res(mAIworld, resourceCount);
		//std::shared_ptr<Resource> res(new Resource(mAIworld, resourceCount));
		Resource* res = new Resource(mAIworld, resourceCount);
		res->Load();

		mResources.push_back(res);
		mAIworld.AddEntity(res);
	}
}

void Game::GenerateResources()
{
	const float width = (float)IniFile_GetInt("WinWidth", 800);
	const float height = (float)IniFile_GetInt("WinHeight", 600);

	for (auto res : mResources)
	{
		int resourceCount = RandomInt(5, 15);
		res->SetResourceCount(resourceCount);	// reset number resources
		res->Spawn(SGE::SVector2(RandomFloat(100.0f, width), RandomFloat(100.0f, height)));
	}
	// Temp hack to prevent the harvester from going to the resource's old position
	mHavester.ChangeState(Idle);
}
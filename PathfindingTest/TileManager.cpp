#include "TileManager.h"
#include <SGE/SGE.h>
using namespace SGE;

TileManager* TileManager::spInstance = nullptr;

TileManager* TileManager::Get()
{
	if (!spInstance)
	{
		spInstance = new TileManager();
	}
	return spInstance;
}

TileManager::TileManager()
	:	mCurrentTileType(0)
	,	mTileTypes(0)
{
}

void TileManager::Init(int tiletypes)
{
	mTileTypes = tiletypes;
}

void TileManager::Update()
{
	if (Input_IsKeyPressed(Keys::ONE))
		mCurrentTileType = 0;
	if (Input_IsKeyPressed(Keys::TWO))
		mCurrentTileType = 1;
}

int TileManager::GetCurrentTile() const
{
	return mCurrentTileType;
}

void TileManager::SetTile(int type)
{
	mCurrentTileType = type;
}

void TileManager::PushToHistory(const TileData& td)
{
	mHistory.push(td);
}

TileData TileManager::GetHistory()
{
	if (mHistory.size())
	{
		TileData td = mHistory.top();
		mHistory.pop();
		return td;
	}
}

int TileManager::HistorySize()
{
	return mHistory.size();
}
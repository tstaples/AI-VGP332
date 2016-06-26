#ifndef INCLUDED_TILEMANAGER_H
#define INCLUDED_TILEMANAGER_H

#include <stack>

struct TileData
{
	int x, y;
	int oldType;
	int newType;
	bool walkable;

	TileData() {}
	TileData(int _x, int _y, int _old, int _new, bool walk)
		:	x(_x), y(_y), oldType(_old), newType(_new), walkable(walk) {}
};

class TileManager
{
	TileManager();

public:
	static TileManager* Get();

	void Init(int tiletypes);
	void Update();
	int GetCurrentTile() const;
	void SetTile(int type);

	void PushToHistory(const TileData& td);
	TileData GetHistory();
	int HistorySize();

private:
	static TileManager* spInstance;
	int mTileTypes;
	int mCurrentTileType;
	
	std::stack<TileData> mHistory;
};

#endif
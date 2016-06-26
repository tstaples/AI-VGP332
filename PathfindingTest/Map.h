#ifndef _MAP_H
#define _MAP_H
#pragma once

#include "Tile.h"
#include "NonCopyable.h"
#include <stack>
using namespace SGE;

class Map : private NonCopyable	// Inherits blocked copy constructor
{
public:
	Map();
	~Map();
	
	// Load all the tile sprites
	void Load(const char *pLevelFile, const char *pTexturePack);

	// Unload all the tile sprites
	void Unload();

	// Update each tile sprite
	void Update(float deltaTime);

	// Render each of the tile sprites
	void Render(const SGE::SVector2& offset);

	SRect GetBoundingBoxFromSegment(const SLineSegment& line) const;

	// Scales the dimensions of the map to the new values
	void Resize(int newRows, int newCols);

	void Save(const char* pLevel);

	// Dimensions of the map
	inline int GetWidth() const		{ return mColumns * mTileSize; }
	inline int GetHeight() const	{ return mRows * mTileSize; }
	inline int GetColumns() const	{ return mColumns; }
	inline int GetRows() const		{ return mRows; }
	inline int GetSpriteCount() const { return mSpriteCount; }
	inline int GetTileSize() const	{ return mTileSize; }

	Tile& GetTile(int x, int y);
	Tile& GetTileAtMouse(int mx, int my);
	Tile& GetTileAtMouse();

private:
	bool LoadLevel(const char* level);
	bool LoadTexturePack(const char* texurePack);

	SGE_Sprite *mSprites;			// Tile textures
	Tile* mTiles;					// 2D array of tiles

	int mColumns;					// # of columns in the grid
	int mRows;						// # of rows in the grid
	int mTileSize;					// Tile sprite dimesion
	int mSpriteCount;				// Number of sprites
};

#endif // #ifndef _MAP_H
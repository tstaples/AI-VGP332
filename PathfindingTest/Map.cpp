#include "Map.h"
#include <fstream>
#include <vector>
#include <string>

Map::Map()
	:	mTiles(nullptr)
	,	mSprites(nullptr)
	,	mColumns(0)
	,	mRows(0)
	,	mTileSize(0)
	,	mSpriteCount(0)
{
	
}
// ----------------------------------------------------------------

Map::~Map()
{
	Unload();
}
// ----------------------------------------------------------------

void Map::Load(const char *pLevelFile, const char *pTexturePack)
{
	// Clean up before we start loading
	Unload();
	
	// Load the level data
	if (!LoadLevel(pLevelFile))
	{
		Unload();
		return;
	}

	// Load the texture pack
	if (!LoadTexturePack(pTexturePack))
	{
		Unload();
		return;
	}
}
// ----------------------------------------------------------------

void Map::Unload()
{
	if (mSprites)
	{
		for (int i=0; i < mSpriteCount; ++i)
		{
			// Unload each of the sprites in the array
			mSprites[i].Unload();
		}
		delete [] mSprites;
		mSprites = nullptr;
	}

	// Clear up tiles
	if (mTiles)
	{
		delete [] mTiles;
		mTiles = nullptr;
	}

	// Reset values
	mColumns = 0;	
	mRows = 0;		
	mTileSize = 0;	
	mSpriteCount = 0;
}
// ----------------------------------------------------------------

void Map::Update(float deltaTime)
{
	// Map scaling
	if (Input_IsKeyPressed(Keys::NUM_ADD))
	{
		Resize(GetRows() + 1, GetColumns() + 1);
	}
	if (Input_IsKeyPressed(Keys::NUM_SUB))
	{
		Resize(GetRows() - 1, GetColumns() - 1);
	}
}
// ----------------------------------------------------------------

void Map::Render(const SGE::SVector2& offset)
{
	for (int y=0; y < mRows; ++y)
	{
		for (int x=0; x < mColumns; ++x)
		{
			// Compute the adress of the tile once and store in reference var
			// reference pointer acts as a const pointer. (ie. const char* const foo);

			const int index = x + (y * mColumns);
			const Tile &tile = mTiles[index];
			const SGE::SVector2& pos = tile.GetPosition();
			const int type = tile.GetType();

			SGE::SGE_Sprite& sprite = mSprites[type];

			// Add the camera offset to so the map scrolls
			sprite.SetPosition(pos + offset);
			sprite.Render();

			// Render visual hit boxes for non-walkable tiles
			if (!tile.IsWalkable())
			{
				SRect bb = tile.GetBoundingBox();
				Graphics_DebugRect(bb + offset, 0x0000ff);
			}
		}
	}
}
// ----------------------------------------------------------------

SRect Map::GetBoundingBoxFromSegment(const SLineSegment& line) const
{
	// Validate line segment (assumes line is vert/horizontal)
	if (line.from.x < 0.0f || line.from.x > GetWidth()  ||
		 line.from.y < 0.0f || line.from.y > GetHeight() ||
		 line.to.x < 0.0f	|| line.to.x > GetWidth()	 ||
		 line.to.y < 0.0f	|| line.to.y > GetHeight())
	{
		// Line segment is out of bounds
		return SRect();
	}

	// Truncate the values to get the grid index
	const int fromX = static_cast< int >(line.from.x) / mTileSize;
	const int fromY = static_cast< int >(line.from.y) / mTileSize;
	const int toX	= static_cast< int >(line.to.x)	  / mTileSize;
	const int toY	= static_cast< int >(line.to.y)	  / mTileSize;

	// Assumes to is larger than from.
	// +1 since we count ourself
	const int countX = toX - fromX + 1;
	const int countY = toY - fromY + 1;

	// Get region (AABB - Axis aligned bounding box)
	// Initialized as invalid (inverted)
	SRect region;
	for (int y=0; y < countY; ++y)
	{
		for (int x=0; x < countX; ++x)
		{
			const unsigned int index = (fromX + x) + ((fromY + y) * mColumns);
			if (!mTiles[index].IsWalkable())
			{
				// Expand the region by the bounding box of the tiles
				region += mTiles[index].GetBoundingBox();
			}
		}
	}
	// Check return value for IsValid(). if not then there is no collision
	return region;
}
// ----------------------------------------------------------------

bool Map::LoadLevel(const char* pLevelFile)
{
	FILE *pFile = nullptr;
	if (fopen_s(&pFile, pLevelFile, "r") == 0)
	{
		// Read map dimensions
		fscanf_s(pFile, "%*s %d", &mColumns);
		fscanf_s(pFile, "%*s %d", &mRows);
		fscanf_s(pFile, "%*s %d", &mTileSize);

		// Allocate tile buffer
		mTiles = new Tile[mRows * mColumns];

		fgetc(pFile);
		for (int y=0; y < mRows; ++y)
		{
			for (int x=0; x < mColumns; ++x)
			{
				const int index = x + (y * mColumns);
				Tile& tile = mTiles[index];

				tile.SetPosition(SGE::SVector2((float)x * mTileSize, (float)y * mTileSize));
				tile.SetSize(mTileSize);
				tile.SetType(fgetc(pFile) - '0');

				// Would need to change based on different tile types
				tile.SetWalkable(tile.GetType() == 0);
				tile.SetValid(true);
			}
			// Get the new line char to move to the next line
			fgetc(pFile);
		}
		fclose(pFile);
		pFile = nullptr;

		return true;
	}
	return false;
}
// ----------------------------------------------------------------

bool Map::LoadTexturePack(const char* texurePack)
{
	FILE *pFile = nullptr;
	if (fopen_s(&pFile, texurePack, "r") == 0)
	{
		// Read number of sprites contained in the file
		fscanf_s(pFile, "%*s %d", &mSpriteCount);
	
		// Create sprite pool
		mSprites = new SGE::SGE_Sprite[mSpriteCount];

		// Read each texture name into the buffer and load it
		for (int i=0; i < mSpriteCount; ++i)
		{
			char buffer[128];
			fscanf_s(pFile, "%s", buffer, 128);
			mSprites[i].Load(buffer);
		}

		fclose(pFile);
		pFile = nullptr;

		return true;
	}
	return false;
}

Tile& Map::GetTile(int x, int y)
{
	const int index = x + (y * mColumns);
	return (mTiles[index]);
}

Tile& Map::GetTileAtMouse(int mx, int my)
{
	const int tx = mx / (GetWidth() / GetColumns());
	const int ty = my / (GetHeight() / GetRows());

	if (mx > GetWidth() || 
		my > GetHeight() ||
		mx < 0 || my < 0)
	{
		// Tile's "isvalid" flag defaults to false.
		// Always check it after calling this function
		return Tile();
	}
	return GetTile(tx, ty);
}

Tile& Map::GetTileAtMouse()
{
	const int mx = Input_GetMouseScreenX();
	const int my = Input_GetMouseScreenY();
	return GetTileAtMouse(mx, my);
}

void Map::Resize(int newRows, int newCols)
{
	const int newSize = newRows * newCols;
	Tile* newTiles = new Tile[newSize];

	for (int y=0; y < newRows; ++y)
	{
		for (int x=0; x < newCols; ++x)
		{
			const int index = x + (y * newCols);
			Tile& tile = newTiles[index];

			// If there is an existing tile at this position, copy it into the new array
			if (mTiles &&
				x < mColumns && 
				y < mRows && 
				index < (mRows * mColumns))
			{
				// If we're expanding the map, set the offset negative so the correct tile is copied
				int offset = y;
				if ((mRows - newRows) < 0)
					offset = -y;

				tile = mTiles[index + offset];
				tile.SetValid(true);
			}
			else
			{
				// No existing tile occupies this space, set as default
				newTiles[index].SetPosition(x * mTileSize, y * mTileSize);
				newTiles[index].SetSize(mTileSize);
				newTiles[index].SetType(0);
				newTiles[index].SetWalkable(true);
				newTiles[index].SetValid(true);
			}
		}
	}

	// Clear the existing tiles
	if (mTiles)
	{
		delete [] mTiles;
	}

	// Link to the new array of tiles
	mTiles = newTiles;
	newTiles = nullptr;
	mRows = newRows;
	mColumns = newCols;
}

void Map::Save(const char* pLevel)
{
	std::ofstream outfile(pLevel, std::ios::trunc);
	if (outfile.is_open())
	{
		// Write map values
		outfile << "Columns: " << mColumns << std::endl;
		outfile << "Rows: " << mRows << std::endl;
		outfile << "TileSize: " << mTileSize << std::endl;

		for (int y=0; y < mRows; ++y)
		{
			for (int x=0; x < mColumns; ++x)
			{
				const int index = x + (y * mColumns);
				Tile& tile = mTiles[index];

				outfile << tile.GetType();
			}
			outfile << std::endl;
		}
		outfile.close();
	}
}
#include <SGE/SGE.h>
#include "PaintTile.h"
#include "TileManager.h"
#include "Map.h"

void PaintTile::Execute(Map& map)
{
	const int mouseX = Input_GetMouseScreenX();
	const int mouseY = Input_GetMouseScreenY();

	Tile& tile = map.GetTileAtMouse(mouseX, mouseY);
	if (tile.IsValid())
	{
		int oldType = tile.GetType();
		int newTileType = TileManager::Get()->GetCurrentTile();
		tile.SetType(newTileType);

		TileManager::Get()->PushToHistory(
			TileData((int)tile.GetPosition().x, 
					 (int)tile.GetPosition().y,
					 oldType,
					 newTileType,
					 tile.IsWalkable())
					 );

		// Temp: all non-grass tiles are non-walkable
		if (newTileType)
			tile.SetWalkable(false);
		else
			tile.SetWalkable(true);
	}
}

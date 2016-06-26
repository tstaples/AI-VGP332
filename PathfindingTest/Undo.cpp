#include "Undo.h"
#include "Map.h"
#include "TileManager.h"

void Undo::Execute(Map& map)
{
	if (TileManager::Get()->HistorySize())
	{
		TileData td = TileManager::Get()->GetHistory();
		Tile& tile = map.GetTileAtMouse(td.x, td.y);
		tile.SetType(td.oldType);
		tile.SetWalkable(td.walkable);
	}
}

#include <SGE/SGE.h>
#include "Save.h"
#include "Map.h"

void Save::Execute(Map& map)
{
	map.Save("level01.txt");
}

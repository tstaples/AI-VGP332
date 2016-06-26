#include "AIFunctorImpl.h"
#include "PaintTile.h"
#include "TileManager.h"
#include <vector>

// ------------------------------------------------------------------------
// Prototypes
// ------------------------------------------------------------------------

void InitCanvas();
void InitGraph();
void GraphDebugRender();
void DrawPath();
void RunSearch(AI::GraphSearch& searchMode, const SearchPoints& sp);
void CheckInput();

// ------------------------------------------------------------------------

void SGE_Initialize()
{
	InitCanvas();
	InitGraph();
}
// ------------------------------------------------------------------------

void SGE_Terminate()
{
	gMap.Unload();
	gCursor.Unload();
	gInputMan.Terminate();
	gGraph.Destroy();
}
// ------------------------------------------------------------------------

bool SGE_Update(float deltaTime)
{
	gCursor.Update(deltaTime);
	TileManager::Get()->Update();
	gInputMan.Update(gMap);
	gMap.Update(deltaTime);

	// Toggle grid debug line render
	if (Input_IsKeyPressed(Keys::G))
		gGridRender = !gGridRender;

	// Toggle drawing full path outline
	if (Input_IsKeyPressed(Keys::F))
		gDrawFullPath = !gDrawFullPath;

	if (Input_IsMousePressed(Mouse::MBUTTON))
	{
		if (!gSearchPoints.start.isset)
		{
			// Set the first point
			gSearchPoints.start.point = gMap.GetTileAtMouse().GetMapCoord();
			gSearchPoints.start.isset = true;
		}
		else if (!gSearchPoints.end.isset)
		{
			// Set the end point
			gSearchPoints.end.point = gMap.GetTileAtMouse().GetMapCoord();
			gSearchPoints.end.isset = true;
		}
		else
		{
			// Reset the first point and invalidate the second
			gSearchPoints.start.point = gMap.GetTileAtMouse().GetMapCoord();
			gSearchPoints.end.isset = false;
			gDrawPath = false;
		}
	}

	// Run the search if the search points are valid
	if (gSearchPoints.Valid())
	{
		if (Input_IsKeyPressed(Keys::F1))
		{
			AI::BreadthFirstSearch search(gGraph, GetDefaultValid());
			RunSearch(search, gSearchPoints);
			gDrawPath = true;
		}
		else if (Input_IsKeyPressed(Keys::F2))
		{
			AI::DepthFirstSearch search(gGraph, GetDefaultValid());
			RunSearch(search, gSearchPoints);
			gDrawPath = true;
		}
		else if (Input_IsKeyPressed(Keys::F3))
		{
			AI::DijkstraSearch search(gGraph, GetG(), GetValid());
			RunSearch(search, gSearchPoints);
			gDrawPath = true;
		}
		else if (Input_IsKeyPressed(Keys::F4))
		{
			AI::AStarSearch search(gGraph, GetG(), GetH_Manhattan(), GetValid());
			RunSearch(search, gSearchPoints);
			gDrawPath = true;
		}
		else if (Input_IsKeyPressed(Keys::F5))
		{
			AI::AStarSearch search(gGraph, GetG(), GetH_Euclidean(), GetValid());
			RunSearch(search, gSearchPoints);
			gDrawPath = true;
		}

	}
	else
	{
		// Don't draw if there aren't valid points
		gDrawPath = false;
	}

	return Input_IsKeyPressed(Keys::ESCAPE);
}
// ------------------------------------------------------------------------

void SGE_Render()
{
	SVector2 offset(0.0f, 0.0f);
	gMap.Render(offset);
	gCursor.Render();

	if (gGridRender)
	{
		GraphDebugRender();
	}

	if (gDrawPath)
	{
		DrawPath();
	}
}
// ------------------------------------------------------------------------

void InitCanvas()
{
	// Visuals for the map
	gMap.Load("level01.txt", "texturepack01.txt");
	gCursor.Load("sword.png");
	gInputMan.Init();
	TileManager::Get()->Init(gMap.GetSpriteCount());
}
// ------------------------------------------------------------------------

void InitGraph()
{
	// Initialize a graph with the same dimensions as our map
	gGraph.Create(gMap.GetColumns(), gMap.GetRows());

	// Second pass over graph to set the position of each node in respect to the
	// corresponding map tile.

	// Offset the position of the node to the center of the tile
	const int kTileSize = gMap.GetTileSize();
	SVector2 offset(kTileSize * 0.5f, kTileSize * 0.5f);

	for (int y=0; y < gMap.GetRows(); ++y)
	{
		for (int x=0; x < gMap.GetColumns(); ++x)
		{
			AI::Node* node = gGraph.GetNode(x, y);
			SVector2 pos((float)x * kTileSize, (float)y * kTileSize);
			node->position = pos + offset;
		}
	}

	// Todo
	//aiworld.AddGraph(gGraph);
}
// ------------------------------------------------------------------------

void GraphDebugRender()
{
	for (int y=0; y < gMap.GetRows(); ++y)
	{
		for (int x=0; x < gMap.GetColumns(); ++x)
		{
			AI::Node* node = gGraph.GetNode(x, y);
			for (int i=0; i < AI::Direction::Count; ++i)
			{
				AI::Node* neighbor = node->neighbors[i];
				if (neighbor)
				{
					Graphics_DebugLine(node->position, neighbor->position);
				}
			}
		}
	}
}
// ------------------------------------------------------------------------

void RunSearch(AI::GraphSearch& search, const SearchPoints& sp)
{
	search.Run(sp.start.point.x, sp.start.point.y,
				sp.end.point.x, sp.end.point.y);

	if (search.IsFound())
	{
		gClosedList.clear();
		gClosedList = search.GetClosedList();
		gEndNode = search.GetPath();
		gDrawPath = true;
	}
}
// ------------------------------------------------------------------------

void DrawPath()
{
	// Draw the full path outline if enabled
	if (gDrawFullPath)
	{
		NodeList::iterator it = gClosedList.begin();
		for (it; it != gClosedList.end(); ++it)
		{
			AI::Node* node = *it;
			if (node && node->parent)
			{
				Graphics_DebugLine(node->position, node->parent->position, 0xFF0000);
			}
		}
	}

	// Outline actual path in blue
	if (gEndNode)
	{
		AI::Node* node = gEndNode;
		while (node->parent)
		{
			Graphics_DebugLine(node->position, node->parent->position, 0x0000FF);
			node = node->parent;
		}
	}
}
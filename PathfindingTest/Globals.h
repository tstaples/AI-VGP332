#ifndef INCLUDED_GLOBALS_H
#define INCLUDED_GLOBALS_H

#include "Map.h"
#include "InputManager.h"
#include <SGE/SGE.h>
#include <AI/AI.h>
#include <map>
#include <list>
#include <memory>

using namespace SGE;

// ------------------------------------------------------------------------
// Typedefs
// ------------------------------------------------------------------------

typedef std::list<AI::Node*> NodeList;
typedef std::unique_ptr<AI::GraphSearch> upGSearch;
typedef std::map<int, upGSearch> SearchMap;

// ------------------------------------------------------------------------
// Globals
// ------------------------------------------------------------------------

Map						gMap;
InputManager			gInputMan;
SGE_Cursor				gCursor;
AI::Graph				gGraph;
bool					gGridRender = false;
NodeList				gClosedList;
AI::Node*				gEndNode = nullptr;
bool					gDrawPath = false;
bool					gDrawFullPath = true;
SearchMap				gSearchMap;

// ------------------------------------------------------------------------
// Structures
// ------------------------------------------------------------------------

struct Point
{
	SVector2 point;
	bool isset;

	Point() : isset(false){}
};

struct SearchPoints
{
	Point start;
	Point end;

	bool Valid()
	{
		return (gSearchPoints.start.isset &&
				gSearchPoints.end.isset);
	}

} gSearchPoints;

enum SearchType
{
	BreadthFirst,
	DepthFirst,
	Dijkstra
};

#endif
#ifndef INCLUDED_AI_H
#define INCLUDED_AI_H

// Entry point for the AI library

#include <string>

// Agent headers
#include "Agent.h"
#include "Entity.h"
#include "AIWorld.h"

// Graph headers
#include "Graph.h"
#include "Node.h"

// Graph searches
#include "BreadthFirstSearch.h"
#include "DepthFirstSearch.h"
#include "DijkstraSearch.h"
#include "AStarSearch.h"

#include "PathPlanner.h"

// Steering headers
#include "SteeringModule.h"
#include "SteeringBehavior.h"

// Steering implementations
#include "SeekBahavior.h"
#include "Arrive.h"
#include "Wander.h"
#include "ObstacleAvoidance.h"
#include "Separate.h"
#include "Alignment.h"
#include "Cohesion.h"

// FSM
#include "State.h"
#include "StateMachine.h"

// Perception
#include "PerceptionModule.h"

// Utility
#include "Coord2.h"

// Cheeky alternative to: 'using std::literals::string_literals::operator"" s;'
// since VS2012 doesn't support C++14 :(
inline std::string S(const char* s) 
{
	return std::string(s);
}

inline std::string S(const char s) 
{
	return std::to_string(s);
}

#endif
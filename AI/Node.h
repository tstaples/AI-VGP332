#ifndef INCLUDED_AI_NODE_H
#define INCLUDED_AI_NODE_H

#include <SGE/SGE.h>
#include <list>

namespace AI
{

enum Direction
{
	North,
	East,
	South,
	West,
	NorthEast,
	NorthWest,
	SouthEast,
	SouthWest,
	Count
};

// TODO: make template
struct Node
{
	// Each node will have at most 8 neighbors since this is grid based
	Node* neighbors[Direction::Count];
	Node* parent;
	SGE::SVector2 position;
	bool open;					// In the open list
	bool closed;				// Node has been checked
	float g;					// Cumulative cost to get to this node
	float h;					// Hueristic

	// T data;
};
typedef std::list<Node*> NodeList;

}	// namespace AI
#endif	// #ifndef INCLUDED_AI_NODE_H
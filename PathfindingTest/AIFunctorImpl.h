#ifndef INCLUDED_AIFUNCTORIMPL_H
#define INCLUDED_AIFUNCTORIMPL_H

#include "Globals.h"

const float CostMatrix[2][2] =
{
	// grass	// stone
	{ 1.0f,		1000.0f },	// grass
	{ 2.5f,		5.0f },		// stone
};
// ------------------------------------------------------------------------

// Functor for calculating the cost to traverse to a ndoe
struct GetG : public AI::ICostFunctor
{
	inline virtual float operator()(AI::Node* a, AI::Node* b) const
	{
		// Get the scalar distance between the nodes
		float distance = Distance(a->position, b->position);
		const float tilesize = 1.0f / gMap.GetTileSize();

		int x1 = (int)(a->position.x * tilesize);
		int y1 = (int)(a->position.y * tilesize);
		int x2 = (int)(b->position.x * tilesize);
		int y2 = (int)(b->position.y * tilesize);

		// Get tile type we're at and where we're going
		int typeA = gMap.GetTile(x1, y1).GetType();
		int typeB = gMap.GetTile(x2, y2).GetType();

		// Look up cost in CostMatrix to go from a to b
		float cost = CostMatrix[typeA][typeB];

		// Multiply the distance by the cost
		return distance * cost;
	}
};
// ------------------------------------------------------------------------

struct GetH_Euclidean : public AI::ICostFunctor
{
	inline virtual float operator()(AI::Node* a, AI::Node* b) const
	{
		// Get the scalar distance between the nodes
		return Distance(a->position, b->position);
	}
};
// ------------------------------------------------------------------------

struct GetH_Manhattan : public AI::ICostFunctor
{
	inline virtual float operator()(AI::Node* a, AI::Node* b) const
	{
		// Get the scalar distance between the nodes
		SVector2 p1 = a->position;
		SVector2 p2 = b->position;
		float xdist = abs(p1.x - p2.x);
		float ydist = abs(p1.y - p2.y);
		
		// http://en.wikipedia.org/wiki/Chebyshev_distance
		return Max(ydist, xdist);
	}
};
// ------------------------------------------------------------------------


// Functor for validating nodes
struct GetValid : public AI::IValid
{
	inline virtual bool operator()(const AI::Node* a) const
	{
		// Node exists
		if (a != nullptr)
		{
			int x = (int)(a->position.x / gMap.GetTileSize());
			int y = (int)(a->position.y / gMap.GetTileSize());
		
			// Type isn't stone
			if (gMap.GetTile(x, y).GetType() != 1)
			{
				return true;
			}
		}
		return false;
	}
};
// ------------------------------------------------------------------------

// Default behaviour for checking validity
struct GetDefaultValid : public AI::IValid
{
	inline virtual bool operator()(const AI::Node* a) const
	{
		// Node exists
		return (a != nullptr);
	}
};

#endif
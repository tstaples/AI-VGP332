#include "DijkstraSearch.h"
#include "Node.h"
#include "Graph.h"

namespace AI
{

DijkstraSearch::DijkstraSearch(Graph& graph, const ICostFunctor& getG, const IValid& getvalid)
	:	GraphSearch(graph, getvalid)
	,	mGetG(getG)
{
}

Node* DijkstraSearch::GetNextNode()
{
	NodeList::iterator lowestIter = mOpenList.end();
	float minG = FLT_MAX;

	NodeList::iterator it = mOpenList.begin();
	for (it; it != mOpenList.end(); ++it)
	{
		Node* node = *it;
		if (node->g < minG)
		{
			minG = node->g;
			lowestIter = it;
		}
	}

	Node* lowestNode = nullptr;
	if (lowestIter != mOpenList.end())
	{
		lowestNode = *lowestIter;
		mOpenList.erase(lowestIter);
	}
	return lowestNode;
}

void DijkstraSearch::ExpandNode(Node* node, Node* neighbor)
{
	// Check if we've been to this neighbor
	if (!neighbor->closed)
	{
		const float g = node->g + mGetG(node, neighbor);
		if (!neighbor->open)
		{
			// Assign the cumulative cost of traveling to this neighbor
			neighbor->g = g;

			// Link the neighbor to this node and add to openlist
			neighbor->parent = node;
			AddToOpen(neighbor);
		}
		else if (g < neighbor->g)
		{
			// Edge relaxation

			// We have visited this node already, but we have found a better path
			neighbor->g = g;
			neighbor->parent = node;
		}
	}
}

};
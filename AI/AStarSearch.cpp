#include "AStarSearch.h"
#include "Node.h"
#include "Graph.h"

namespace AI
{

AStarSearch::AStarSearch(Graph& graph, 
						 const ICostFunctor& getG, 
						 const ICostFunctor& getH, 
						 const IValid& getvalid)
	:	GraphSearch(graph, getvalid)
	,	mGetG(getG)
	,	mGetH(getH)
{
}

Node* AStarSearch::GetNextNode()
{
	NodeList::iterator lowestIter = mOpenList.end();
	float minF = FLT_MAX;

	NodeList::iterator it = mOpenList.begin();
	for (it; it != mOpenList.end(); ++it)
	{
		Node* node = *it;
		if (node->g + node->h < minF)
		{
			minF = node->g + node->h;
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

void AStarSearch::ExpandNode(Node* node, Node* neighbor)
{
	// Check if we've been to this neighbor
	if (!neighbor->closed)
	{
		const float g = node->g + mGetG(node, neighbor);
		if (!neighbor->open)
		{
			// Assign the cumulative cost of traveling to this neighbor
			neighbor->g = g;

			// Assign the heuristic which is the distance from the current node to the end
			neighbor->h = mGetH(mEndNode, neighbor);

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
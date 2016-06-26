#include "BreadthFirstSearch.h"
#include "Node.h"
#include "Graph.h"

namespace AI
{

BreadthFirstSearch::BreadthFirstSearch(Graph& graph, const IValid& getvalid)
	:	GraphSearch(graph, getvalid)
{
}

Node* BreadthFirstSearch::GetNextNode()
{
	Node* node = mOpenList.front();
	mOpenList.pop_front();
	return node;
}

void BreadthFirstSearch::ExpandNode(Node* node, Node* neighbor)
{
	// Check if we've been to this neighbor
	if (!neighbor->open && !neighbor->closed)
	{
		// Link the neighbor to this node and add to openlist
		neighbor->parent = node;
		AddToOpen(neighbor);
	}
}

};
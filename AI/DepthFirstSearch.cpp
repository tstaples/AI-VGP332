#include "DepthFirstSearch.h"
#include "Node.h"
#include "Graph.h"

namespace AI
{

DepthFirstSearch::DepthFirstSearch(Graph& graph, const IValid& getvalid)
	:	GraphSearch(graph, getvalid)
{
}

Node* DepthFirstSearch::GetNextNode()
{
	Node* node = mOpenList.back();
	mOpenList.pop_back();
	return node;
}

void DepthFirstSearch::ExpandNode(Node* node, Node* neighbor)
{
	// Check if we've been to this neighbor
	if (!neighbor->open && !neighbor->closed)
	{
		// Link the neighbor to this node and add to openlist
		neighbor->parent = node;
		AddToOpen(neighbor);
	}
}

//bool DepthFirstSearch::IsValid(const Node* node) const
//{
//	//return (node != nullptr);
//	return GraphSearch::IsValid(node);
//}

};
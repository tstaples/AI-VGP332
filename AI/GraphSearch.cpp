#include "GraphSearch.h"
#include "Graph.h"
#include "Node.h"

namespace AI
{

GraphSearch::GraphSearch(Graph& graph, const IValid& getvalid)
	:	mGraph(graph)
	,	mFound(false)
	,	mEndNode(nullptr)
	,	mGetValid(getvalid)
{
}

void GraphSearch::Run(UINT startx, UINT starty, UINT endx, UINT endy)
{
	Node* startnode = mGraph.GetNode(startx, starty);
	mEndNode = mGraph.GetNode(endx, endy);

	if (!startnode || !mEndNode)
	{
		return;
	}

	// Reset Graph nodes
	mGraph.ResetNodes();

	// Add start node to open list
	AddToOpen(startnode);

	bool done = false;
	while (!done && !mOpenList.empty())
	{
		// The way the next node is retrieved is determined by the
		// derived GraphSearch type this was called by.
		Node* node = GetNextNode();

		if (node == mEndNode)
		{
			done = true;
			mFound = true;
		}
		else
		{
			// Iterate through all neighboring nodes
			for (int i=0; i < AI::Direction::Count; ++i)
			{
				AI::Node* neighbor = node->neighbors[i];
				if (IsValid(neighbor))
				{
					// Call derived class specific implementation of expanding the node
					ExpandNode(node, neighbor);
				}
			}
		}
		// Add the node to the closed list
		AddToClosed(node);
	}
}

Node* GraphSearch::GetPath() const
{
	if (mFound)
	{
		return mEndNode;
	}
	return nullptr;
}

NodeList GraphSearch::GetClosedList() const
{
	return mClosedList;
}

void GraphSearch::AddToOpen(Node* node)
{
	mOpenList.push_back(node);
	node->open = true;
}

void GraphSearch::AddToClosed(Node* node)
{
	mClosedList.push_back(node);
	node->closed = true;
}

bool GraphSearch::IsValid(const Node* node) const
{
	return mGetValid(node);
}

}; // namespace AI
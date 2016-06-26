#include "Graph.h"
#include "Node.h"

namespace AI
{

Graph::Graph()
	:	mNodes(nullptr)
	,	mRows(0)
	,	mColumns(0)
{
}

Graph::~Graph()
{
	Destroy();
}

void Graph::Create(unsigned int cols, unsigned int rows)
{
	// Clear existing
	Destroy();

	// Allocate 1D array of total nodes needed
	mNodes = new Node[cols * rows];
	mColumns = cols;
	mRows = rows;

	// Connect node neighbors
	for (unsigned int y=0; y < rows; ++y)
	{
		for (unsigned int x=0; x < cols; ++x)
		{
			Node *node = GetNode(x, y);
			if (node)
			{
				// Invalid neighbors are returned as null
				node->neighbors[North]		= GetNode(x		, y - 1	);
				node->neighbors[East]		= GetNode(x + 1	, y		);
				node->neighbors[South]		= GetNode(x		, y + 1	);
				node->neighbors[West]		= GetNode(x - 1	, y		);
				node->neighbors[NorthEast]	= GetNode(x + 1	, y - 1	);
				node->neighbors[NorthWest]	= GetNode(x - 1	, y - 1	);
				node->neighbors[SouthEast]	= GetNode(x + 1	, y + 1	);
				node->neighbors[SouthWest]	= GetNode(x - 1	, y + 1	);
			}
		}
	}
}

void Graph::Destroy()
{
	if (mNodes)
	{
		delete [] mNodes;
		mNodes = nullptr;
		mRows = 0;
		mColumns = 0;
	}
}

Node* Graph::GetNode(unsigned int x, unsigned int y)
{
	if (x >= 0 && x < mColumns &&
		y >= 0 && y < mRows)
	{
		const unsigned int index = x + (y * mColumns);
		return &mNodes[index];
	}
	return nullptr;
}

void Graph::ResetNodes()
{
	const unsigned int sz = mRows * mColumns;
	for (unsigned int i=0; i < sz; ++i)
	{
		Node& node = mNodes[i];
		node.parent = nullptr;
		node.open = false;
		node.closed = false;
		node.g = 0.0f;
		node.h = 0.0f;
	}
}

};
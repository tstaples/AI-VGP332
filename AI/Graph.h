#ifndef INCLUDED_AI_GRAPH_H
#define INCLUDED_AI_GRAPH_H

#include <list>

namespace AI
{

struct Node;

class Graph
{
public:
	Graph();
	~Graph();

	// Inits the nodes and their links.
	// Node data must be initialized afterwards by whatever is using this
	void Create(unsigned int cols, unsigned int rows);

	// Deletes the graph
	void Destroy();

	// Returns null if index is out of range
	Node* GetNode(unsigned int x, unsigned int y);

	// Sets parents to null, closed and open values to false
	void ResetNodes();

private:
	// TODO
	Graph(const Graph& rhs);
	Graph& operator=(const Graph& rhs);

	Node* mNodes;			// 1D array simulating a 2D array
	unsigned int mColumns;
	unsigned int mRows;
};
typedef std::list<Node*> NodeList;

}; // namespace AI
#endif	// #ifndef INCLUDED_AI_GRAPH_H
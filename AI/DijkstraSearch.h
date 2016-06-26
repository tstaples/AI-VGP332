#ifndef INCLUDED_AI_DIJKSTRASEARCH_H
#define INCLUDED_AI_DIJKSTRASEARCH_H

#include "GraphSearch.h"

namespace AI
{

class DijkstraSearch : public GraphSearch
{
public:
	// getG must be defined by whatever is using this search.
	DijkstraSearch(Graph& graph, const ICostFunctor& getG, const IValid& getvalid);

private:
	virtual Node* GetNextNode();
	virtual void ExpandNode(Node* node, Node* neighbor);

	// returns cumulative cost for a node
	const ICostFunctor& mGetG;
};

};
#endif
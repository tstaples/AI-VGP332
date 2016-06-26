#ifndef INCLUDED_AI_ASTARSEARCH_H
#define INCLUDED_AI_ASTARSEARCH_H

#include "GraphSearch.h"

namespace AI
{

class AStarSearch : public GraphSearch
{
public:
	// getG must be defined by whatever is using this search.
	AStarSearch(Graph& graph, 
				const ICostFunctor& getG, 
				const ICostFunctor& getH, 
				const IValid& getvalid);

private:
	virtual Node* GetNextNode();
	virtual void ExpandNode(Node* node, Node* neighbor);

	// returns cumulative cost for a node
	const ICostFunctor& mGetG;
	const ICostFunctor& mGetH;
};

};
#endif
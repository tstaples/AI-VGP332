#ifndef INCLUDED_AI_DEPTHFIRSTSEARCH_H
#define INCLUDED_AI_DEPTHFIRSTSEARCH_H

#include "GraphSearch.h"

namespace AI
{

class DepthFirstSearch : public GraphSearch
{
public:
	DepthFirstSearch(Graph& graph, const IValid& getv);

private:
	virtual Node* GetNextNode();
	virtual void ExpandNode(Node* node, Node* neighbor);
	//virtual bool IsValid(const Node* node) const;
};

};
#endif
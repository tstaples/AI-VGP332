#ifndef INCLUDED_AI_BREADFIRSTSEARCH_H
#define INCLUDED_AI_BREADFIRSTSEARCH_H

#include "GraphSearch.h"

namespace AI
{

class BreadthFirstSearch : public GraphSearch
{
public:
	BreadthFirstSearch(Graph& grap, const IValid& getvalidh);

private:
	virtual Node* GetNextNode();
	virtual void ExpandNode(Node* node, Node* neighbor);
};

};
#endif
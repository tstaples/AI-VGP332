#ifndef INCLUDED_AI_GRAPHSEARCH_H
#define INCLUDED_AI_GRAPHSEARCH_H

#include <vector>
#include <cassert>
#include "Node.h"

namespace AI
{

class Graph;

// Functor interface declarations
struct ICostFunctor
{
	virtual float operator()(AI::Node* a, AI::Node* b) const = 0;
};

struct IValid
{
	virtual bool operator()(const Node* a) const = 0;
};


class GraphSearch
{
	typedef unsigned int UINT;

public:
	GraphSearch(Graph& graph, const IValid& getvalid);

	// Run the graph search
	void Run(UINT startx, 
			 UINT starty, 
			 UINT endx,
			 UINT endy);

	// Pushes all the nodes for the path into the vector passed in
	Node* GetPath() const;
	NodeList GetClosedList() const;
	
	// todo: draw full propgation
	// iterate through closedlist and draw lines from that index to any neighbors

	bool IsFound() const { return mFound; }

	void Clear();

protected:
	virtual Node* GetNextNode() = 0;
	virtual void ExpandNode(Node* node, Node* neighbor) = 0;
	virtual bool IsValid(const Node* node) const;

	void AddToOpen(Node* node);
	void AddToClosed(Node* node);

protected:
	// TODO: list of handles
	Graph& mGraph;				// Reference to the graph we're searching
	bool mFound;				// Value was found
	Node* mEndNode;				// Node we are looking for

	NodeList mOpenList;			// Nodes to search
	NodeList mClosedList;		// Nodes that have been searched

	const IValid& mGetValid;
};

};	// namespace AI
#endif	// INCLUDED_AI_GRAPHSEARCH_H
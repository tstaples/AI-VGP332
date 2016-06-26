#ifndef INCLUDED_AI_GRID_H
#define INCLUDED_AI_GRID_H

struct Node;

class Grid
{
public:
	Grid();
	~Grid();

	void Create(unsigned int cols, unsigned int rows);
	void Destroy();

	// Returns null if index is out of range
	Node* GetNode(unsigned int x, unsigned int y);

private:
	Node* mNodes;			// 1D array simulating a 2D array
	unsigned int mColumns;
	unsigned int mRows;
};

#endif	// #ifndef INCLUDED_AI_GRAPH_H
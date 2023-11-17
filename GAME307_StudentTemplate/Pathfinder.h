#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <queue>
#include <unordered_map>

#include "Grid.h"

class GridGraph;

// custom compare class, so we can use my own struct inside the priority queue
// it just compares the m_score value
class Compare
{
public:
	bool operator() (Node* a, Node* b)
	{
		return a->m_score > b->m_score;
	}

};

class Pathfinder {
private:
	float heuristic(Node* start, Node* target);
	std::vector<int> generateResultPath(std::unordered_map<int, int> cameFrom, Node* startNode, Node* targetNode);

public:
	void calculateBFS( Node* startNode, Node* targetNode, GridGraph* graph, std::vector<int> &res );
	void calculateGreedy(Node* startNode, Node* targetNode, GridGraph* graph, std::vector<int>& res);
	void calculateAStar(Node* startNode, Node* targetNode, GridGraph* graph, std::vector<int>& res);

};

#endif // !PATHFINDER_H

#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H
#include <unordered_map>
#include <SDL.h>

class Grid;
struct Node;

// struct for calculating the four directions in the Euclidean space
struct Direction {
	int x{ 0 };
	int y{ 0 };
};

// graph from a grid style space
class GridGraph {
private:
	Grid* m_sourceGrid{ nullptr };
	// the graph stores the tiles by its index, not its location; and every tile is only connected to its neighbor
	// that is why there is no Connection variable for every tile
	std::unordered_map<int, Node*> m_nodeMap;
	Direction m_dirs[4] = { Direction{1,0}, Direction{-1,0}, Direction{0,1}, Direction{0,-1}  };

public:
	GridGraph(Grid* grid);

	std::vector<Node*> getNeighbors(int idx);
	void HandleEvents(const SDL_Event& event);
	Node* getNodeFromIdx(int idx) { return m_nodeMap[idx]; };
};

#endif // !GRIDGRAPH_H

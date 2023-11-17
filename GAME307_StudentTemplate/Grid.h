#ifndef GRID_H
#define GRID_H

#include <SDL.h>
#include <vector>
#include "Rectangle.h"

// struct to store the necessary information for a tile or node on the grid
struct Node {
	int m_X{ 0 };
	int m_Y{ 0 };
	float m_score{ FLT_MAX };
	bool m_wall{ false };
	int m_id{ 0 };

	Rectangle m_rect;

	Node() {};
	Node(int x, int y, int idx)
		: m_X(x)
		, m_Y(y)
		, m_id(idx)
	{}
};

// grid class to represent the tilegrid of the map
class Grid {
private:
	int m_width{ 0 };
	int m_heigth{ 0 };
	int m_windowW{ 0 };
	int m_windowH{ 0 };

	std::vector<std::vector<Node*>> m_grid;

	Node* startNode{};
	Node* targetNode{};

	void CreateGrid();

public:
	// the number of rows and columns are inputs here, so we can change that easily
	Grid(int width, int heigth, int windowWidth, int windowHeigth)
		: m_width(width)
		, m_heigth(heigth)
		, m_windowW(windowWidth)
		, m_windowH(windowHeigth)
	{
		CreateGrid();
	}
	~Grid();

	void Render(SDL_Renderer* renderer);
	void HandleEvents(const SDL_Event& event);

	std::vector<std::vector<Node*>> getGridVector() { return m_grid; };
	// overload the getter to get either the index of the node or the node itself
	bool getNodeForPoint(int x, int y, int &res);
	bool getNodeForPoint(int x, int y, Node* &res);

	int getWidth() { return m_width; };
	int getHeigth() { return m_heigth; };

	Node* getStartNode() { return startNode; };
	Node* getTargetNode() { return targetNode; };

	void resetStartTargetNodes();

};

#endif // !GRID_H

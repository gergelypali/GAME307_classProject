#include "GridGraph.h"
#include "Grid.h"

GridGraph::GridGraph(Grid* grid)
{
	m_sourceGrid = grid;
	for (auto const& oneCol : grid->getGridVector())
	{
		for (auto oneNode : oneCol)
		{
			// using a map that stores the index of the tile and the tile itself
			m_nodeMap[oneNode->m_id] = oneNode;
		}
	}
}

// calculate real time the neighbors of a given tile
// if it is a wall or a given color(2) mean it is not a valid tile
std::vector<Node*> GridGraph::getNeighbors(int idx)
{
	std::vector<Node*> res;

	for (auto const& dir : m_dirs)
	{
		int neighborX = m_nodeMap[idx]->m_X + dir.x;
		int neighborY = m_nodeMap[idx]->m_Y + dir.y;
		if (neighborX < 0 ||
			neighborX >= m_sourceGrid->getWidth() ||
			neighborY < 0 ||
			neighborY >= m_sourceGrid->getHeigth()
			)
			continue;
		auto goodTile = m_sourceGrid->getGridVector()[neighborX][neighborY];
		if (goodTile->m_wall)
			continue;
		if (goodTile->m_rect.getColor() == 2)
			continue;
		res.push_back(goodTile);
	}

	return res;
}

// this was for debugging the getNeighbors function
void GridGraph::HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		int idx{ 0 };
		if (m_sourceGrid->getNodeForPoint(mouseX, mouseY, idx))
			getNeighbors(idx);
	}
}

#include "Grid.h"

Grid::~Grid()
{
	for (auto oneCol : m_grid)
		for (auto node : oneCol)
			delete node;
	m_grid.clear();
}

void Grid::Render(SDL_Renderer* renderer)
{
	for (auto& oneRow : m_grid)
		for (auto& oneNode : oneRow)
			oneNode->m_rect.Render(renderer);
}

void Grid::HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		Node* node{ nullptr };
		if (getNodeForPoint(mouseX, mouseY, node))
		{
			// left click for creating walls or destroying them
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (node->m_rect.getColor() == 2)
					node->m_rect.reColorTo(0);
				else
					node->m_rect.reColorTo(2);
			}
			// right click to mark the start and target nodes
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (startNode == nullptr)
				{
					startNode = node;
					node->m_rect.reColorTo(3);
				}
				else if (targetNode == nullptr && node != startNode)
				{
					targetNode = node;
					node->m_rect.reColorTo(3);
				}
			}
		}
	}
	else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		// reset the start and target nodes
		if (event.key.keysym.scancode == SDL_SCANCODE_R)
			resetStartTargetNodes();
	}
}

void Grid::CreateGrid()
{
	float horizontalPart{ static_cast<float>(m_windowW) / static_cast<float>(m_width) };
	float verticalPart{ static_cast<float>(m_windowH) / static_cast<float>(m_heigth) };
	int id{ 0 };

	m_grid.resize(m_width, std::vector<Node*>(m_heigth));

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_heigth; j++)
		{
			m_grid[i][j] = new Node(i, j, id);
			// split up the screen evenly to create rectangles
			m_grid[i][j]->m_rect = Rectangle{ i * horizontalPart + horizontalPart / 2, j * verticalPart + verticalPart / 2, horizontalPart, verticalPart, 0 };

			id++;
		}
	}
}

bool Grid::getNodeForPoint(int x, int y, int &res)
{
	for (auto& oneCol : m_grid)
		for (auto oneNode : oneCol)
			if (oneNode->m_rect.pointInObstacle(x, y))
			{
				res = oneNode->m_id;
				return true;
			}
	return false;
}

bool Grid::getNodeForPoint(int x, int y, Node* &res)
{
	for (auto& oneCol : m_grid)
		for (auto oneNode : oneCol)
			if (oneNode->m_rect.pointInObstacle(x, y))
			{
				res = oneNode;
				return true;
			}
	return false;
}

void Grid::resetStartTargetNodes()
{
	if (startNode)
		startNode->m_rect.reColorTo(0);
	if (targetNode)
		targetNode->m_rect.reColorTo(0);

	startNode = nullptr;
	targetNode = nullptr;
}

#include "Pathfinder.h"
#include "GridGraph.h"
#include <thread>

// here we can define our own heuristic function
float Pathfinder::heuristic(Node* start, Node* target)
{
	//return abs(start->m_X - target->m_X) + abs(start->m_Y - target->m_Y); // Manhattan distance
	return sqrtf(powf(abs(start->m_X - target->m_X), 2) + powf(abs(start->m_Y - target->m_Y), 2)); // Euclidean distance; for better, more straight pathfinding
}

std::vector<int> Pathfinder::generateResultPath(std::unordered_map<int, int> cameFrom, Node* startNode, Node* targetNode)
{
	// create the path from the came_from map
	std::vector<int> res_path{};
	int current = targetNode->m_id;
	// if there is no targetNode in the map, that means we have not found it, so skip this part
	if (cameFrom.count(current) == 0)
		return res_path;
	while (current != startNode->m_id)
	{
		res_path.push_back(current);
		current = cameFrom[current];
	}
	res_path.push_back(startNode->m_id);
	// reverse the vector so we are going from start to finish
	std::reverse(res_path.begin(), res_path.end());
	return res_path;
}

void Pathfinder::calculateBFS(Node* startNode, Node* targetNode, GridGraph* graph, std::vector<int>& res )
{
	std::queue<Node*> m_frontier;
	m_frontier.push(startNode);
	std::unordered_map<int, int> came_from{};
	came_from[startNode->m_id] = -1;

	while (!m_frontier.empty())
	{
		Node* currentNode = m_frontier.front();
		m_frontier.pop();

		if (currentNode->m_id == targetNode->m_id)
			break;

		for (Node* neighborNode : graph->getNeighbors(currentNode->m_id))
		{
			if (came_from.count(neighborNode->m_id) == 0)
			{
				m_frontier.push(neighborNode);
				came_from[neighborNode->m_id] = currentNode->m_id;
			}
		}
	}

	res = generateResultPath(came_from, startNode, targetNode);
}

void Pathfinder::calculateGreedy(Node* startNode, Node* targetNode, GridGraph* graph, std::vector<int>& res)
{
	// standard priority queue with custom compare class, that I defined in the header file
	std::priority_queue<Node*, std::vector<Node*>, Compare> m_frontier;
	m_frontier.push(startNode);
	std::unordered_map<int, int> came_from{};
	came_from[startNode->m_id] = -1;

	while (!m_frontier.empty())
	{
		Node* currentNode = m_frontier.top();
		m_frontier.pop();

		if (currentNode->m_id == targetNode->m_id)
			break;

		for (Node* neighborNode : graph->getNeighbors(currentNode->m_id))
		{
			if (came_from.count(neighborNode->m_id) == 0)
			{
				neighborNode->m_score = heuristic(targetNode, neighborNode);
				m_frontier.push(neighborNode);
				came_from[neighborNode->m_id] = currentNode->m_id;
			}
		}
	}

	res = generateResultPath(came_from, startNode, targetNode);
}

void Pathfinder::calculateAStar(Node* startNode, Node* targetNode, GridGraph* graph, std::vector<int>& res)
{
	std::priority_queue<Node*, std::vector<Node*>, Compare> m_frontier;
	m_frontier.push(startNode);
	std::unordered_map<int, int> came_from{};
	came_from[startNode->m_id] = -1;
	std::unordered_map<int, int> cost_so_far{};
	cost_so_far[startNode->m_id] = 0;

	while (!m_frontier.empty())
	{
		Node* currentNode = m_frontier.top();
		m_frontier.pop();

		if (currentNode->m_id == targetNode->m_id)
			break;

		for (Node* neighborNode : graph->getNeighbors(currentNode->m_id))
		{
			int new_cost = cost_so_far[currentNode->m_id] + 1; // using one because the travel cost in this grid is always 1
			if (cost_so_far.count(neighborNode->m_id) == 0 || new_cost < cost_so_far[neighborNode->m_id])
			{
				cost_so_far[neighborNode->m_id] = new_cost;
				neighborNode->m_score = new_cost + heuristic(targetNode, neighborNode);
				m_frontier.push(neighborNode);
				came_from[neighborNode->m_id] = currentNode->m_id;
			}
		}
	}

	res = generateResultPath(came_from, startNode, targetNode);
}

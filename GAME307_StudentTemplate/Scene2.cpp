#include "Scene2.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Pathfinder.h"
#include <thread>

Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	SDL_GetWindowSize(window, &xAxis, &yAxis);
}

Scene2::~Scene2(){
}

bool Scene2::OnCreate() {
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// create a grid on the map with tiles
	m_grid = new Grid(20, 20, w, h);

	// create a graph from the grid layout
	m_graph = new GridGraph(m_grid);

	// pathfinder object
	m_pathFinder = new Pathfinder();

	return true;
}

void Scene2::OnDestroy() {
	delete m_grid;
	delete m_graph;
	delete m_pathFinder;
}

void Scene2::Update(const float deltaTime) {
	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene2::calculatePath(int idx)
{
	auto start = m_grid->getStartNode();
	auto target = m_grid->getTargetNode();
	if (!start || !target)
		return;
	// calculate the path based on the choosen algorithm
	switch (idx)
	{
		case 1:
			m_pathFinder->calculateBFS(m_grid->getStartNode(), m_grid->getTargetNode(), m_graph, m_resPath);
			break;
		case 2:
			m_pathFinder->calculateGreedy(m_grid->getStartNode(), m_grid->getTargetNode(), m_graph, m_resPath);
			break;
		case 3:
			m_pathFinder->calculateAStar(m_grid->getStartNode(), m_grid->getTargetNode(), m_graph, m_resPath);
			break;
		default:
			break;
	}
	// draw out the path we have found
	for (int i : m_resPath)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		m_graph->getNodeFromIdx(i)->m_rect.reColorTo(1);
		m_grid->Render(renderer);
		SDL_RenderPresent(renderer);
	}
}

void Scene2::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// first because it is in the background
	m_grid->Render(renderer);

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		// keywords to the three different algorithms
		if (event.key.keysym.scancode == SDL_SCANCODE_T)
			calculatePath(1);
		if (event.key.keysym.scancode == SDL_SCANCODE_G)
			calculatePath(2);
		if (event.key.keysym.scancode == SDL_SCANCODE_B)
			calculatePath(3);
		// reset the found path by the pathfinder
		if (event.key.keysym.scancode == SDL_SCANCODE_R)
		{
			for (int i : m_resPath)
			{
				m_graph->getNodeFromIdx(i)->m_rect.reColorTo(0);
			}
			m_resPath.clear();
		}
	}

	m_grid->HandleEvents(event);
	m_graph->HandleEvents(event);

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

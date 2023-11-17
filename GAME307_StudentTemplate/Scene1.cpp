#include "Scene1.h"
#include "StaticNPC.h"
#include "KinematicSteeringOutput.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Pathfinder.h"
#include <thread>

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	SDL_GetWindowSize(window, &xAxis, &yAxis);

	// create a NPC
	blinky = nullptr;
}

Scene1::~Scene1(){
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

bool Scene1::OnCreate() {
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

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png") )
	{
		return false;
	}

	// static body Clyde part
	Body* statiClydeBody = new Body(Vec3{ 25,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 50.0f, 0, 90.0f, 0);
	SDL_Texture* clydeTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Clyde.png"));
	statiClyde = std::make_unique<StaticNPC>(this, statiClydeBody, clydeTexture, 0.15f);
	npcVector.push_back(statiClyde.get());

	// dynamic body Clyde part
	Body* dynamiClydeBody = new Body(Vec3{ float(w)/2,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 30.0f, 40.0f, 90.0f, 180.0f);
	dynamiClyde = std::make_unique<DynamicNPC>(this, dynamiClydeBody, clydeTexture, 0.15f);
	npcVector.push_back(dynamiClyde.get());

	// create more dynamic bodies so I can showcase the separation function also
	Body* dynamiClydeBody2 = new Body(Vec3{ float(w) / 2 + 40,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 30.0f, 40.0f, 90.0f, 180.0f);
	dynamiClyde2 = std::make_unique<DynamicNPC>(this, dynamiClydeBody2, clydeTexture, 0.15f);
	npcVector.push_back(dynamiClyde2.get());

	Body* dynamiClydeBody3 = new Body(Vec3{ float(w) / 2 - 40,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 30.0f, 40.0f, 90.0f, 180.0f);
	dynamiClyde3 = std::make_unique<DynamicNPC>(this, dynamiClydeBody3, clydeTexture, 0.15f);
	npcVector.push_back(dynamiClyde3.get());

	// end of character set ups

	// create a grid on the map with tiles
	m_grid = new Grid(20, 20, w, h);

	// create a graph from the grid layout
	m_graph = new GridGraph(m_grid);

	// pathfinder object
	m_pathFinder = new Pathfinder();

	// Obstacle setup / circles
	//obstacleVector.push_back(new Circle{ w / 2, h / 2, 50 });
	//obstacleVector.push_back(new Circle{ w / 2 + 200, h / 2 + 200, 50 });
	//obstacleVector.push_back(new Circle{ w / 2 - 200, h / 2, 50 });

	return true;
}

void Scene1::OnDestroy() {
	for (auto& oneC : obstacleVector)
		delete oneC;
	delete m_grid;
	delete m_graph;
	delete m_pathFinder;
}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's
	// blinky->Update(deltaTime);

	statiClyde->Update(deltaTime);

	dynamiClyde->Update(deltaTime);
	dynamiClyde2->Update(deltaTime);
	dynamiClyde3->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::calculatePath(int idx)
{
	auto start = m_grid->getStartNode();
	auto target = m_grid->getTargetNode();
	if (!start || !target)
		return;
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
	for (int i : m_resPath)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		m_graph->getNodeFromIdx(i)->m_rect.reColorTo(1);
		m_grid->Render(renderer);
		SDL_RenderPresent(renderer);
	}
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// first because it is in the background
	m_grid->Render(renderer);

	// draw obstacles with white color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
	for (auto& oneC : obstacleVector)
		oneC->Render(renderer);

	// render any npc's
	//blinky->render(0.15f);
	//statiClyde->Render();

	//dynamiClyde->Render();
	//dynamiClyde2->Render();
	//dynamiClyde3->Render();

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
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
	// send events to npc's as needed

	m_grid->HandleEvents(event);
	m_graph->HandleEvents(event);

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

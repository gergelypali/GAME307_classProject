#include "Scene1.h"
#include "StaticNPC.h"
#include "KinematicSteeringOutput.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Scene1DynamicNPC.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	SDL_GetWindowSize(window, &xAxis, &yAxis);
}

Scene1::~Scene1(){}

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

	// static body Clyde part
	Body* statiClydeBody = new Body(Vec3{ 25,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 50.0f, 0, 90.0f, 0);
	SDL_Texture* clydeTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Clyde.png"));
	statiClyde = std::make_unique<StaticNPC>(this, statiClydeBody, clydeTexture, 0.15f);
	npcVector.push_back(statiClyde.get());

	// dynamic body Clyde part
	Body* dynamiClydeBody = new Body(Vec3{ float(w)/2,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 30.0f, 40.0f, 90.0f, 180.0f);
	dynamiClyde = std::make_unique<Scene1DynamicNPC>(this, dynamiClydeBody, clydeTexture, 0.15f);
	npcVector.push_back(dynamiClyde.get());

	// create more dynamic bodies so I can showcase the separation function also
	Body* dynamiClydeBody2 = new Body(Vec3{ float(w) / 2 + 40,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 30.0f, 40.0f, 90.0f, 180.0f);
	dynamiClyde2 = std::make_unique<Scene1DynamicNPC>(this, dynamiClydeBody2, clydeTexture, 0.15f);
	npcVector.push_back(dynamiClyde2.get());

	Body* dynamiClydeBody3 = new Body(Vec3{ float(w) / 2 - 40,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 30.0f, 40.0f, 90.0f, 180.0f);
	dynamiClyde3 = std::make_unique<Scene1DynamicNPC>(this, dynamiClydeBody3, clydeTexture, 0.15f);
	npcVector.push_back(dynamiClyde3.get());

	// end of character set ups

	// Obstacle setup / circles
	obstacleVector.push_back(new Circle{ w / 2, h / 2, 50 });
	obstacleVector.push_back(new Circle{ w / 2 + 200, h / 2 + 200, 50 });
	obstacleVector.push_back(new Circle{ w / 2 - 200, h / 2, 50 });

	return true;
}

void Scene1::OnDestroy() {
	for (auto& oneC : obstacleVector)
		delete oneC;
}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's

	statiClyde->Update(deltaTime);

	dynamiClyde->Update(deltaTime);
	dynamiClyde2->Update(deltaTime);
	dynamiClyde3->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// draw obstacles with white color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0);
	for (auto& oneC : obstacleVector)
		oneC->Render(renderer);

	// render any npc's
	statiClyde->Render();

	dynamiClyde->Render();
	dynamiClyde2->Render();
	dynamiClyde3->Render();

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

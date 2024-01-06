#include "Scene3.h"
#include "Scene3DynamicNPCTree.h"
#include "Scene3DynamicNPCSM.h"

Scene3::Scene3(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	SDL_GetWindowSize(window, &xAxis, &yAxis);
}

Scene3::~Scene3(){
}

bool Scene3::OnCreate() {
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

	SDL_Texture* clydeTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Clyde.png"));

	// dynamic body Clyde part
	Body* dynamiClydeBody = new Body(Vec3{ float(w)/2,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 30.0f, 40.0f, 90.0f, 180.0f);
	dynamiClyde = std::make_unique<Scene3DynamicNPCTree>(this, dynamiClydeBody, clydeTexture, 0.15f);

	Body* dynamiClydeBody2 = new Body(Vec3{ float(w)/2 + 200,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 30.0f, 40.0f, 90.0f, 180.0f);
	dynamiClyde2 = std::make_unique<Scene3DynamicNPCSM>(this, dynamiClydeBody2, clydeTexture, 0.15f);

	// end of character set ups

	return true;
}

void Scene3::OnDestroy() {
}

void Scene3::Update(const float deltaTime) {

	// update the NPC
	dynamiClyde->Update(deltaTime);
	dynamiClyde2->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene3::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	dynamiClyde->Render();
	dynamiClyde2->Render();

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene3::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

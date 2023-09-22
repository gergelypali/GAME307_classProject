#include "Scene1.h"
#include "StaticNPC.h"
#include "KinematicSteeringOutput.h"

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
	int w, h;
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
	Body* statiClydeBody = new Body(Vec3{ 25,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 5.0f, 0, 90.0f, 0);
	SDL_Texture* clydeTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load("Clyde.png"));
	statiClyde = std::make_unique<StaticNPC>(this, statiClydeBody, clydeTexture, 0.15f);

	// dynamic body Clyde part
	Body* dynamiClydeBody = new Body(Vec3{ 25,25,0 }, Vec3{}, Vec3{}, 0, 0, 0.0f, 0, 0, 50.0f, 100.0f, 90.0f, 180.0f);
	dynamiClyde = std::make_unique<DynamicNPC>(this, dynamiClydeBody, clydeTexture, 0.15f);

	// end of character set ups

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's
	//blinky->Update(deltaTime);

	statiClyde->Update(deltaTime);

	dynamiClyde->Update(deltaTime);

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	//blinky->render(0.15f);
	statiClyde->Render();

	dynamiClyde->Render();

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

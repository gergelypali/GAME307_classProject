#ifndef SCENE1_H
#define SCENE1_H

#include <MMath.h>
#include <VMath.h>
#include "Scene.h"
#include "Character.h"
#include "StaticNPC.h"
#include "DynamicNPC.h"

class Obstacle;

using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window *window;
	int w, h;
	int xAxis = 0;
	int yAxis = 0;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
    Matrix4 inverseProjection;

	Character* blinky;

	std::unique_ptr<StaticNPC>statiClyde{nullptr};
	std::unique_ptr<DynamicNPC>dynamiClyde{nullptr};
	std::unique_ptr<DynamicNPC>dynamiClyde2{nullptr};
	std::unique_ptr<DynamicNPC>dynamiClyde3{nullptr};

	std::vector<NPCInterface*> npcVector{};
	std::vector<Obstacle*> obstacleVector{};

public:
	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
    void HandleEvents(const SDL_Event &event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
    Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	SDL_Renderer* getRenderer() { return renderer; }
	std::vector<NPCInterface*> getNPCVector() { return npcVector; }
	std::vector<Obstacle*> getObstacleVector() { return obstacleVector; }
};

#endif

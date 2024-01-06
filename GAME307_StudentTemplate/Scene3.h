#ifndef SCENE3_H
#define SCENE3_H

#include <MMath.h>
#include <VMath.h>
#include "Scene.h"

class Scene3DynamicNPCTree;
class Scene3DynamicNPCSM;

using namespace MATH;
class Scene3 : public Scene {
private:
	SDL_Window *window;
	int w, h;
	int xAxis = 0;
	int yAxis = 0;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
    Matrix4 inverseProjection;

	std::unique_ptr<Scene3DynamicNPCTree>dynamiClyde{nullptr};
	std::unique_ptr<Scene3DynamicNPCSM>dynamiClyde2{nullptr};

public:
	Scene3(SDL_Window* sdlWindow, GameManager* game_);
	~Scene3();
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
	std::vector<NPCInterface*> getNPCVector() { return std::vector<NPCInterface*>{}; }
	std::vector<Obstacle*> getObstacleVector() { return std::vector<Obstacle*>{}; }
};

#endif

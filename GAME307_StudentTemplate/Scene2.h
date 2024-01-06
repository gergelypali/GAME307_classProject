#ifndef SCENE2_H
#define SCENE2_H

#include <MMath.h>
#include <VMath.h>
#include "Scene.h"

class Grid;
class GridGraph;
class Pathfinder;

using namespace MATH;
class Scene2 : public Scene {
private:
	SDL_Window *window;
	int w, h;
	int xAxis = 0;
	int yAxis = 0;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
    Matrix4 inverseProjection;

	// variables for pathfinding
	Grid* m_grid{ nullptr };
	GridGraph* m_graph{ nullptr };
	Pathfinder* m_pathFinder{ nullptr };
	std::vector<int> m_resPath;
	void calculatePath(int idx);

public:
	Scene2(SDL_Window* sdlWindow, GameManager* game_);
	~Scene2();
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

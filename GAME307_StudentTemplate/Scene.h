#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "GameManager.h"
#include <vector>

using namespace MATH;

class NPCInterface;
class Obstacle;

class Scene {
public:
    class GameManager* game = NULL;
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
    virtual void HandleEvents(const SDL_Event& event) = 0;
    virtual ~Scene(){};
	virtual float getxAxis() = 0;
	virtual float getyAxis() = 0;
	virtual SDL_Window* getWindow() = 0;
    virtual Matrix4 getProjectionMatrix() = 0;
	virtual Matrix4 getInverseMatrix() = 0;
	virtual SDL_Renderer* getRenderer() = 0;
	virtual std::vector<NPCInterface*> getNPCVector() = 0;
	virtual std::vector<Obstacle*> getObstacleVector() = 0;
};

#endif

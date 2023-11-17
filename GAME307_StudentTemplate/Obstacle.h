#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <Vector.h>
#include <SDL.h>

struct collisionData
{
	MATH::Vec3 position;
	MATH::Vec3 normal;
};

// base class for any kind of obstacle, you have to define the render and collision function for each
class Obstacle
{
public:
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual collisionData GetCollision(MATH::Vec3 pos, MATH::Vec3 ray) = 0;
	virtual bool pointInObstacle(float x, float y) = 0;

};

#endif // !OBSTACLE_H

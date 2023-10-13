#ifndef CIRCLE_H
#define CIRCLE_H

#include "Obstacle.h"

// basic circle obstacle
class Circle : public Obstacle
{
private:
	int m_centerX{};
	int m_centerY{};
	int m_radius{};

public:
	Circle(int centerX, int centerY, int radius) {
		m_centerX = centerX;
		m_centerY = centerY;
		m_radius = radius;
	};

	void Render(SDL_Renderer* renderer);
	collisionData GetCollision(MATH::Vec3 pos, MATH::Vec3 ray);
};

#endif // !CIRCLE_H

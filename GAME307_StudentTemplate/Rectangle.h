#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Obstacle.h"
#include <vector>

class Rectangle : public Obstacle
{
private:
	float m_x{ 0 };
	float m_y{ 0 };
	float m_width{ 0 };
	float m_height{ 0 };

	int m_currentColorIdx{ 0 };
	// store the available colors in a ringbuffer
	std::vector<SDL_Color> m_colorRing{
		SDL_Color{ 0xFF, 0, 0xFF, 0 },
		SDL_Color{ 0, 0xFF, 0, 0 },
		SDL_Color{ 0, 0, 0, 0},
		SDL_Color{ 0xFF, 0, 0, 0}
	};
	SDL_Color m_color{ m_colorRing[0] };
	SDL_Color m_borderColor{ 0xFF, 0xFF, 0xFF, 0 };

public:
	Rectangle() {};
	Rectangle(float centerX, float centerY, float width, float height, int color)
	{
		m_x = centerX - width / 2;
		m_y = centerY - height / 2;
		m_width = width;
		m_height = height;
		m_currentColorIdx = color;
		m_color = m_colorRing[m_currentColorIdx];
	}

	void Render(SDL_Renderer* renderer);
	collisionData GetCollision(MATH::Vec3 pos, MATH::Vec3 ray);
	bool pointInObstacle(float x, float y);
	void pickNextColorFromRing();
	void reColorTo(int idx);
	int getColor() { return m_currentColorIdx; };

};

#endif // !RECTANGLE_H

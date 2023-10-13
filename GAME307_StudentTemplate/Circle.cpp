#include "Circle.h"
#include <VMath.h>

using namespace MATH;

void Circle::Render(SDL_Renderer* renderer)
{
	const int32_t diameter = (m_radius * 2);

	int32_t x = (m_radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		// Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, m_centerX + x, m_centerY - y);
		SDL_RenderDrawPoint(renderer, m_centerX + x, m_centerY + y);
		SDL_RenderDrawPoint(renderer, m_centerX - x, m_centerY - y);
		SDL_RenderDrawPoint(renderer, m_centerX - x, m_centerY + y);
		SDL_RenderDrawPoint(renderer, m_centerX + y, m_centerY - x);
		SDL_RenderDrawPoint(renderer, m_centerX + y, m_centerY + x);
		SDL_RenderDrawPoint(renderer, m_centerX - y, m_centerY - x);
		SDL_RenderDrawPoint(renderer, m_centerX - y, m_centerY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

collisionData Circle::GetCollision(Vec3 pos, Vec3 ray)
{
	// used the same algorithm as in GAMEPHYSICS3 for the 3D sphere
	collisionData res{};

	Vec3 m{ pos - Vec3{float(m_centerX), float(m_centerY), 0.f} };
	float b{ VMath::dot(m, ray) };
	float c{ VMath::dot(m, m) - m_radius * m_radius };
	if (c > 0.f && b > 0.f)
		return res;
	float disc{ b * b - c };
	if (disc < 0.f)
		return res;
	float t{ std::max(-b - sqrtf(disc), 0.f) };
	
	res.position = pos + ray * t;
	res.normal = VMath::normalize(res.position - Vec3{ float(m_centerX), float(m_centerY), 0.f});

	return res;
}

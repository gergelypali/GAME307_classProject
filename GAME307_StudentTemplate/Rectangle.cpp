#include "Rectangle.h"

void Rectangle::pickNextColorFromRing()
{
	m_currentColorIdx++;
	if (m_currentColorIdx == m_colorRing.size())
		m_currentColorIdx = 0;
	m_color = m_colorRing[m_currentColorIdx];
}

void Rectangle::Render(SDL_Renderer* renderer)
{
	SDL_FRect theRect{};
	theRect.x = m_x;
	theRect.y = m_y;
	theRect.w = m_width;
	theRect.h = m_height;

	SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, 0);
	SDL_RenderFillRectF(renderer, &theRect);
	SDL_SetRenderDrawColor(renderer, m_borderColor.r, m_borderColor.g, m_borderColor.b, 0);
	SDL_RenderDrawRectF(renderer, &theRect);
}

// just a simple default collisionData, because we dont want to do collision with these for now
collisionData Rectangle::GetCollision(MATH::Vec3 pos, MATH::Vec3 ray)
{
	return collisionData{};
}

bool Rectangle::pointInObstacle(float x, float y)
{
	if (x > m_x && x < m_x + m_width // x component checking
		&& y > m_y && y < m_y + m_height) // y component checking
	{
		return true;
	}
	return false;
}

void Rectangle::reColorTo(int idx)
{
	m_currentColorIdx = idx;
	m_color = m_colorRing[m_currentColorIdx];
}

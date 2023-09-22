#ifndef NPC_H
#define NPC_H

#include "Body.h"
#include "Scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Behaviour.h"

template <class T>
class NPC
{
private:
	SDL_Texture* m_texture{ nullptr };
	float m_scale{ 1.0f };

protected:
	Scene* m_currentScene{ nullptr };
	Body* m_body{ nullptr };
	T* m_behaviour{ nullptr };

public:
	NPC(Scene* currentScene, Body* body, SDL_Texture* texture, float scale, T* behaviour) :
		m_currentScene(currentScene),
		m_body(body),
		m_texture(texture),
		m_scale(scale),
		m_behaviour(behaviour)
	{};
	~NPC()
	{
		if (m_body)
			delete m_body;
		if (m_behaviour)
			delete m_behaviour;
	};

	virtual void Update(float deltaTime) = 0;
	void Render()
	{
		SDL_Renderer* renderer = m_currentScene->getRenderer();
		Matrix4 projectionMatrix = m_currentScene->getProjectionMatrix();

		SDL_Rect square;
		Vec3 screenCoords;
		int w, h;

		// notice use of "body" in the following
		SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);
		w = static_cast<int>(w * m_scale);
		h = static_cast<int>(h * m_scale);
		screenCoords = projectionMatrix * m_body->getPos();
		square.x = static_cast<int>(screenCoords.x - 0.5f * w);
		square.y = static_cast<int>(screenCoords.y - 0.5f * h);
		square.w = w;
		square.h = h;

		// Convert character orientation from radians to degrees.
		float orientation = m_body->getOrientation();

		SDL_RenderCopyEx(renderer, m_texture, nullptr, &square,
			orientation, nullptr, SDL_FLIP_NONE);
	};
};

#endif // !NPC_H
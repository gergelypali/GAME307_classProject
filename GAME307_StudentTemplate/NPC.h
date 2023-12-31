#ifndef NPC_H
#define NPC_H

#include "Body.h"
#include "Scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Behaviour.h"

class NPCInterface
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	Body* m_body{ nullptr };

};

template <class T>
class NPC : public NPCInterface
{
private:
	SDL_Texture* m_texture{ nullptr };
	float m_scale{ 1.0f };

protected:
	T* m_behaviour{ nullptr };
	Scene* m_currentScene{ nullptr };

public:
	NPC(Scene* currentScene, Body* body, SDL_Texture* texture, float scale, T* behaviour) :
		m_currentScene(currentScene),
		m_texture(texture),
		m_scale(scale),
		m_behaviour(behaviour)
	{
		m_body = body;
	};
	~NPC()
	{
		if (m_body)
			delete m_body;
		if (m_behaviour)
			delete m_behaviour;
	};

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

	void Update(float deltaTime) override
	{
		// update the NPC's movement based on the player's state
		m_behaviour->Update(m_currentScene->game->getPlayer(), m_body);
		// upadte the NPC's movement based on the other NPC's state
		m_behaviour->Update(m_currentScene->getNPCVector(), m_body);
		// upadte the NPC's movement based on the obstacles
		m_behaviour->Update(m_currentScene->getObstacleVector(), m_body);

		// update method for an only static/kinematic body
		m_body->setPos(m_body->getPos() + m_body->getVel() * deltaTime);
		m_body->setOrientation(m_body->getOrientation() + m_body->getRotation() * deltaTime);

		// update the dynamic values also
		m_body->setVel(m_body->getVel() + m_body->getAccel() * deltaTime);
		m_body->setRotation(m_body->getRotation() + m_body->getAngular() * deltaTime);

		if (MATH::VMath::mag(m_body->getVel()) > m_body->getMaxSpeed())
		{
			m_body->setVel(MATH::VMath::normalize(m_body->getVel()) * m_body->getMaxSpeed());
		}
	}
};

#endif // !NPC_H

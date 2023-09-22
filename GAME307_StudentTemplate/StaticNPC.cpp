#include "StaticNPC.h"

void StaticNPC::Update(float deltaTime)
{
	m_behaviour->Update(m_currentScene->game->getPlayer(), m_body);

	// update method for an only static/kinematic body
	m_body->setPos(m_body->getPos() + m_body->getVel() * deltaTime);
	m_body->setOrientation(m_body->getOrientation() + m_body->getRotation() * deltaTime);
}

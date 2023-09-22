#include "DynamicNPC.h"

void DynamicNPC::Update(float deltaTime)
{
	m_behaviour->Update(m_currentScene->game->getPlayer(), m_body);

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

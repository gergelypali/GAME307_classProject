#ifndef KINEMATIC_H
#define KINEMATIC_H

#include "Body.h"

class Kinematic : public Body
{
public:
	Kinematic() : Body() {};
	Kinematic(
		Vec3 position,
		float orientation,
		Vec3 velocity,
		float rotation
	) : Body(
		position,
		velocity,
		Vec3{},
		0.0f,
		0.0f,
		orientation,
		rotation,
		0.0f,
		maxSpeed,
		0.0f,
		maxRotation,
		0.0f
	) {};
	~Kinematic() {};

	Vec3 m_position;
	float m_orientation;
	Vec3 m_velocity;
	float m_rotation;

	void Update(float deltaTime);
};

#endif // !KINEMATIC_H

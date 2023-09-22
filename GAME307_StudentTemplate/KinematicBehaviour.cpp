#include "KinematicBehaviour.h"

float KinematicBehaviour::changeOrientation(float current, MATH::Vec3 velocity)
{
	if (MATH::VMath::mag(velocity) > 0)
	{
		return atan2f(velocity.x, velocity.y) * 180.0f / M_PI;
	}
	return current;
}

kinematicSteeringOutput KinematicBehaviour::kinematicSeek(Body* targetBody, Body* charBody)
{
	MATH::Vec3 velocity{ MATH::VMath::normalize(targetBody->getPos() - charBody->getPos()) * charBody->getMaxSpeed() };
	charBody->setOrientation(changeOrientation(charBody->getOrientation(), velocity));
	return kinematicSteeringOutput{ velocity, 0.0f };
}

kinematicSteeringOutput KinematicBehaviour::kinematicFlee(Body* targetBody, Body* charBody)
{
	kinematicSteeringOutput res{ kinematicSeek(targetBody, charBody) };
	return kinematicSteeringOutput{ -1 * res.velocity, -1 * res.rotation };
}

kinematicSteeringOutput KinematicBehaviour::kinematicArrive(Body* targetBody, Body* charBody)
{
	kinematicSteeringOutput res{ kinematicSeek(targetBody, charBody) };
	if (MATH::VMath::mag(targetBody->getPos() - charBody->getPos()) < 100.0f)
	{
		res.velocity = Vec3{};
		return res;
	}
	return res;
}

kinematicSteeringOutput KinematicBehaviour::kinematicWander(Body* targetBody, Body* charBody)
{
	if (MATH::VMath::mag(charBody->getVel()) == 0)
	{
		charBody->setVel(MATH::VMath::normalize(targetBody->getPos() - charBody->getPos()) * charBody->getMaxSpeed());
		charBody->setOrientation(changeOrientation(charBody->getOrientation(), charBody->getVel()));
	}
	return kinematicSteeringOutput{ MATH::Vec3( sinf(charBody->getOrientation() * M_PI / 180.0f), cosf(charBody->getOrientation() * M_PI / 180.0f), 0 ) * charBody->getMaxSpeed(), normalDistribution(generator) * charBody->getMaxRotation() };
}

kinematicSteeringOutput KinematicBehaviour::kinematicPursue(Body* targetBody, Body* charBody)
{
	float maxPrediction{ 0.2f };
	float distance{ MATH::VMath::mag(targetBody->getPos() - charBody->getPos()) };

	float charSpeed{ MATH::VMath::mag(charBody->getVel()) };

	float prediction{ 0 };
	if (charSpeed <= distance / maxPrediction)
	{
		prediction = maxPrediction;
	}
	else
	{
		prediction = distance / charSpeed;
	}

	auto fakeTarget = std::make_unique<Body>(*targetBody);
	fakeTarget->setPos(fakeTarget->getPos() + fakeTarget->getVel() * prediction);

	return kinematicSeek(fakeTarget.get(), charBody);
}

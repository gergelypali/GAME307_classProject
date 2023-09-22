#include "DynamicBehaviour.h"

dynamicSteeringOutput DynamicBehaviour::dynamicSeek(Body* targetBody, Body* charBody)
{
	return dynamicSteeringOutput{ MATH::VMath::normalize(targetBody->getPos() - charBody->getPos()) * charBody->getMaxAcceleration(), 0 };
}

dynamicSteeringOutput DynamicBehaviour::dynamicArrive(Body* targetBody, Body* charBody)
{
	dynamicSteeringOutput res{ dynamicSeek(targetBody, charBody) };
	if (MATH::VMath::mag(targetBody->getPos() - charBody->getPos()) < 100.0f)
	{
		res.acceleration = MATH::VMath::normalize(targetBody->getPos() - charBody->getPos()) * // targetVelocity
			charBody->getMaxSpeed() * MATH::VMath::mag(targetBody->getPos() - charBody->getPos()) / 100.0f // targetSpeed
			- charBody->getVel();
		res.acceleration /= 0.1f;
	}
	return res;
}

dynamicSteeringOutput DynamicBehaviour::dynamicAlign(Body* targetBody, Body* charBody)
{
	dynamicSteeringOutput res{ MATH::Vec3{}, 0.0f };
	float nativeRot = targetBody->getOrientation() - charBody->getOrientation();
	float nativeRotAbs = fabsf(nativeRot);
	float targetRot{};
	if (nativeRotAbs < 1.0f)
	{
		return res;
	}
	if (nativeRotAbs > 25.0f)
	{
		targetRot = charBody->getMaxRotation();
	}
	else
	{
		targetRot = charBody->getMaxRotation() * nativeRotAbs / 25.0f;
	}
	targetRot *= nativeRot / nativeRotAbs;
	res.angularAccel = targetRot - charBody->getRotation();
	if (fabsf(res.angularAccel) > charBody->getMaxAngular())
	{
		res.angularAccel /= fabsf(res.angularAccel);
		res.angularAccel *= charBody->getMaxAngular();
	}

	return res;
}

dynamicSteeringOutput DynamicBehaviour::dynamicVelocityMatch(Body* targetBody, Body* charBody)
{
	dynamicSteeringOutput res{ Vec3{}, 0.0f };

	res.acceleration = targetBody->getVel() - charBody->getVel();
	if (MATH::VMath::mag(res.acceleration) > charBody->getMaxAcceleration())
	{
		res.acceleration = MATH::VMath::normalize(res.acceleration) * charBody->getMaxAcceleration();
	}

	return res;
}

dynamicSteeringOutput DynamicBehaviour::dynamicPursue(Body* targetBody, Body* charBody)
{
	// not my favourite algorithm, I prefer to use kinematic values; velocity instead of acceleration
	// acceleration makes it more slow to respond and easily overshoot
	// of course we can fix the overshooting, but we have to modify the algorithm
	// so it means we are not using the code from the book.
	float maxPrediction{0.2f};
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

	return dynamicArrive(fakeTarget.get(), charBody);
}

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

dynamicSteeringOutput DynamicBehaviour::dynamicFace(Body* targetBody, Body* charBody)
{
	// this is kinda wrong here, when we are at the ends, either +PI or -PI
	// the next frame will go to the opposite end +PI->-PI -PI->+PI
	// an the NPC will do a 360 because the acceleration will move the
	// characters orientation to the other end
	dynamicSteeringOutput res{ MATH::Vec3{}, 0 };

	auto fakeTarget = std::make_unique<Body>(*targetBody);
	auto direction{ fakeTarget->getPos() - charBody->getPos() };
	if (MATH::VMath::mag(direction) == 0)
	{
		return res;
	}
	fakeTarget->setOrientation(atan2f(direction.x, direction.y) * 180.0f / M_PI);
	res = dynamicAlign(fakeTarget.get(), charBody);

	return res;
}

dynamicSteeringOutput DynamicBehaviour::dynamicLookWhereYoureGoing(Body* targetBody, Body* charBody)
{
	dynamicSteeringOutput res{ MATH::Vec3{}, 0 };

	auto charVel{ charBody->getVel() };
	if (MATH::VMath::mag(charVel) == 0)
	{
		return res;
	}

	auto fakeTarget = std::make_unique<Body>(*targetBody);
	fakeTarget->setOrientation(atan2f(charVel.x, charVel.y) * 180.0f / M_PI);
	res = dynamicAlign(fakeTarget.get(), charBody);

	return res;
}

dynamicSteeringOutput DynamicBehaviour::dynamicWander(Body* targetBody, Body* charBody)
{
	dynamicSteeringOutput res{ MATH::Vec3{}, 0 };

	float wanderOrientation{ 0 };
	wanderOrientation += normalDistribution(generator) * 90.0f;
	auto targetOrientation = wanderOrientation + charBody->getOrientation();

	MATH::Vec3 target{ charBody->getPos() + 10.0f * MATH::Vec3(sinf(charBody->getOrientation() * M_PI / 180.0f), cosf(charBody->getOrientation() * M_PI / 180.0f), 0) };
	target += 10.0f * MATH::Vec3(sinf(targetOrientation * M_PI / 180.0f), cosf(targetOrientation * M_PI / 180.0f), 0);

	auto fakeTarget = std::make_unique<Body>(*targetBody);
	fakeTarget->setPos(target);
	res = dynamicFace(fakeTarget.get(), charBody);
	res.acceleration = MATH::VMath::normalize(MATH::Vec3(sinf(charBody->getOrientation() * M_PI / 180.0f), cosf(charBody->getOrientation() * M_PI / 180.0f), 0)) * charBody->getMaxAcceleration();

	return res;
}

dynamicSteeringOutput DynamicBehaviour::dynamicSeparation(std::vector<NPCInterface*> npcVector, Body* charBody)
{
	dynamicSteeringOutput res{ MATH::Vec3{}, 0 };

	float threshold{ 50.f };
	float decayCoeff{ 1.f };

	for (auto npc : npcVector)
	{
		auto direction{ npc->m_body->getPos() - charBody->getPos() };
		// check if this is us, so we can skip the rest of the for loop
		if (direction.x == 0 && direction.y == 0)
			continue;
		float distance{ VMath::mag(direction) };
		if (distance < threshold)
		{
			float strength{ charBody->getMaxAcceleration() };
			res.acceleration -= strength * VMath::normalize(direction);
		}
	}

	return res;
}

dynamicSteeringOutput DynamicBehaviour::dynamicObstacleAvoidance(std::vector<Obstacle*> obstacleVector, Body* charBody)
{
	dynamicSteeringOutput res{ MATH::Vec3{}, 0 };

	float avoidDistance{ 50.f };
	float lookAhead{ 75.f };
	float objectDistance{ lookAhead };
	collisionData finalData{};

	// create a ray for checking the collisions
	if (charBody->getVel().x == 0 && charBody->getVel().y == 0)
		return res;

	auto ray{ VMath::normalize(charBody->getVel()) * lookAhead };

	// do the collision check with every other obstacle
	for (auto &oneO : obstacleVector)
	{
		auto resColl = oneO->GetCollision(charBody->getPos(), ray);
		if (objectDistance > VMath::mag(resColl.position - charBody->getPos()))
		{
			objectDistance = VMath::mag(resColl.position - charBody->getPos());
			finalData = resColl;
		}
	}
	// if there is no collision point inside the lookahead, just skip the rest
	if (objectDistance == lookAhead)
		return res;

	auto fakeTarget = std::make_unique<Body>();
	fakeTarget->setPos(finalData.position + finalData.normal * avoidDistance);
	return dynamicSeek(fakeTarget.get(), charBody);
}

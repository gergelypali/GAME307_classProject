#include "KinematicSteeringOutput.h"

void KinematicSteeringOutput::Update(Body* targetBody, Body* charBody)
{
	auto res{ kinematicArrive(targetBody, charBody) };
	charBody->setVel(res.velocity);
	charBody->setRotation(res.rotation);
}

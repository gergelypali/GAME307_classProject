#include "KinematicSteeringOutput.h"

void KinematicSteeringOutput::Update(Body* targetBody, Body* charBody)
{
	auto res{ kinematicArrive(targetBody, charBody) };
	charBody->setVel(res.velocity);
	charBody->setRotation(res.rotation);
}

void KinematicSteeringOutput::Update(std::vector<NPCInterface*> npcVector, Body* charBody) {}

void KinematicSteeringOutput::Update(std::vector<Obstacle*> obstacleVector, Body* charBody) {}

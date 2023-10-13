#include "DynamicNPCBehaviour.h"

void DynamicNPCBehaviour::Update(Body* targetBody, Body* charBody)
{
	auto resAr{ dynamicSeek(targetBody, charBody) };
	charBody->setAcceleration(resAr.acceleration);
	auto resAl{ dynamicLookWhereYoureGoing(targetBody, charBody) };
	charBody->setAngular(resAl.angularAccel);
}

void DynamicNPCBehaviour::Update(std::vector<NPCInterface*> npcVector, Body* charBody)
{
	auto resAr{ dynamicSeparation(npcVector, charBody) };
	if(resAr.acceleration.x != 0 && resAr.acceleration.y != 0)
		charBody->setAcceleration(resAr.acceleration);
}

void DynamicNPCBehaviour::Update(std::vector<Obstacle*> obstacleVector, Body* charBody)
{
	auto resAr{ dynamicObstacleAvoidance(obstacleVector, charBody) };
	if(resAr.acceleration.x != 0 && resAr.acceleration.y != 0)
		charBody->setAcceleration(resAr.acceleration);
}

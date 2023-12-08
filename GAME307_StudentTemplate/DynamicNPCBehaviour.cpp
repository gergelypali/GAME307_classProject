#include "DynamicNPCBehaviour.h"

void DynamicNPCBehaviour::Update(Body* targetBody, Body* charBody)
{
	auto resA = tree->makeDecision(targetBody, charBody);
	//auto resA = stateM->Update(targetBody, charBody);
	auto resAr{ dynamicSeek(targetBody, charBody) };
	charBody->setAcceleration(resA.acceleration);
	auto resAl{ dynamicLookWhereYoureGoing(targetBody, charBody) };
	charBody->setAngular(resA.angularAccel);
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

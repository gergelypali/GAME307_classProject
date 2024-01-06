#include "Scene3DynamicBehaviourTree.h"

void Scene3DynamicBehaviourTree::Update(Body* targetBody, Body* charBody)
{
	auto resA = tree->makeDecision(targetBody, charBody);
	charBody->setAcceleration(resA.acceleration);
	charBody->setAngular(resA.angularAccel);
}

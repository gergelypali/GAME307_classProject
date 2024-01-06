#include "Scene3DynamicBehaviourSM.h"

void Scene3DynamicBehaviourSM::Update(Body* targetBody, Body* charBody)
{
	auto resA = stateM->Update(targetBody, charBody);
	charBody->setAcceleration(resA.acceleration);
	charBody->setAngular(resA.angularAccel);
}

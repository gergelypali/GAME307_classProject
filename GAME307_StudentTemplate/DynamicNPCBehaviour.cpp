#include "DynamicNPCBehaviour.h"

void DynamicNPCBehaviour::Update(Body* targetBody, Body* charBody)
{
	//auto resAr{ kinematicPursue(targetBody, charBody) };
	//charBody->setVel(resAr.velocity);
	auto resAr{ dynamicPursue(targetBody, charBody) };
	charBody->setAcceleration(resAr.acceleration);
	auto resAl{ dynamicAlign(targetBody, charBody) };
	charBody->setAngular(resAl.angularAccel);
}

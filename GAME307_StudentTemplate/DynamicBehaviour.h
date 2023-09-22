#ifndef DYNAMIC_BEHAVIOUR_H
#define DYNAMIC_BEHAVIOUR_H

#include "KinematicBehaviour.h"

struct dynamicSteeringOutput
{
	MATH::Vec3 acceleration;
	float angularAccel;
};

class DynamicBehaviour : public KinematicBehaviour
{
protected:
	dynamicSteeringOutput dynamicSeek(Body* targetBody, Body* charBody);
	dynamicSteeringOutput dynamicArrive(Body* targetBody, Body* charBody);
	dynamicSteeringOutput dynamicAlign(Body* targetBody, Body* charBody);
	dynamicSteeringOutput dynamicVelocityMatch(Body* targetBody, Body* charBody);
	dynamicSteeringOutput dynamicPursue(Body* targetBody, Body* charBody);
};

#endif // !DYNAMIC_BEHAVIOUR_H

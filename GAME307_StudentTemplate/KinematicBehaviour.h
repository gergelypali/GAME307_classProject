#ifndef KINEMATIC_BEHAVIOUR_H
#define KINEMATIC_BEHAVIOUR_H

#include "Behaviour.h"

struct kinematicSteeringOutput
{
	MATH::Vec3 velocity;
	float rotation;
};

class KinematicBehaviour : public Behaviour
{
protected:
	float changeOrientation(float current, MATH::Vec3 velocity);
	kinematicSteeringOutput kinematicSeek(Body* targetBody, Body* charBody);
	kinematicSteeringOutput kinematicFlee(Body* targetBody, Body* charBody);
	kinematicSteeringOutput kinematicArrive(Body* targetBody, Body* charBody);
	kinematicSteeringOutput kinematicWander(Body* targetBody, Body* charBody);
	kinematicSteeringOutput kinematicPursue(Body* targetBody, Body* charBody);
};

#endif // !KINEMATIC_BEHAVIOUR_H

#ifndef KINEMATIC_STEERING_OUTPUT_H
#define KINEMATIC_STEERING_OUTPUT_H

#include "KinematicBehaviour.h"

class KinematicSteeringOutput : public KinematicBehaviour
{
public:
	KinematicSteeringOutput() {};

	void Update(Body* targetBody, Body* charBody) override;
};

#endif // !KINEMATIC_STEERING_OUTPUT_H

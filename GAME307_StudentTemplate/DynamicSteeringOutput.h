#ifndef DYNAMIC_STEERING_OUTPUT_H
#define DYNAMIC_STEERING_OUTPUT_H

#include "Behaviour.h"

class DynamicSteeringOutput : public Behaviour
{
private:

public:
	DynamicSteeringOutput() {};

	void Update(MATH::Vec3 targetPos, MATH::Vec3 charPos) override;
};

#endif // !DYNAMIC_STEERING_OUTPUT_H

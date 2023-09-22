#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <Vector.h>
#include <random>
#include "Body.h"

class Behaviour
{
protected:
	// random number generators; one uniform and one normal
	std::default_random_engine generator;
	std::uniform_real_distribution<float> uniformDistribution{0.0f, 1.0f};
	std::normal_distribution<float> normalDistribution{0.0f, 1.0f};

public:
	Behaviour() {
		std::cout << "behaviour start!" << std::endl;
	};
	~Behaviour() {
		std::cout << "behaviour end!" << std::endl;
	};

	virtual void Update(Body* targetBody, Body* charBody) = 0;
};

#endif // !BEHAVIOUR_H

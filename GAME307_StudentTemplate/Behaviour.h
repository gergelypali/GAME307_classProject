#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <Vector.h>
#include <random>
#include "Body.h"
#include "NPC.h"
#include "Obstacle.h"

class Behaviour
{
protected:
	// random number generators; one uniform and one normal
	std::default_random_engine generator;
	std::uniform_real_distribution<float> uniformDistribution{0.0f, 1.0f};
	std::normal_distribution<float> normalDistribution{0.0f, 1.0f};

public:
	Behaviour() {};
	~Behaviour() {};

	// different updates for different scenarios
	// one target body update
	virtual void Update(Body* targetBody, Body* charBody) = 0;
	// use this when we are interacting with other NPCs
	virtual void Update(std::vector<NPCInterface*> npcVector, Body* charBody) = 0;
	// obstacle handling update
	virtual void Update(std::vector<Obstacle*> obstacleVector, Body* charBody) = 0;
};

#endif // !BEHAVIOUR_H

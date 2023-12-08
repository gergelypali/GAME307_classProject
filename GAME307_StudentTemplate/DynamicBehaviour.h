#ifndef DYNAMIC_BEHAVIOUR_H
#define DYNAMIC_BEHAVIOUR_H

#include "KinematicBehaviour.h"
#include "NPC.h"
#include "Obstacle.h"

struct dynamicSteeringOutput
{
	MATH::Vec3 acceleration;
	float angularAccel;
};

// the "topmost" class, so we should use this for any "real" behaviour
class DynamicBehaviour : public KinematicBehaviour
{
public:
	static dynamicSteeringOutput dynamicSeek(Body* targetBody, Body* charBody);
	static dynamicSteeringOutput dynamicArrive(Body* targetBody, Body* charBody);
	static dynamicSteeringOutput dynamicAlign(Body* targetBody, Body* charBody);
	static dynamicSteeringOutput dynamicVelocityMatch(Body* targetBody, Body* charBody);
	static dynamicSteeringOutput dynamicPursue(Body* targetBody, Body* charBody);
	static dynamicSteeringOutput dynamicFace(Body* targetBody, Body* charBody);
	static dynamicSteeringOutput dynamicLookWhereYoureGoing(Body* targetBody, Body* charBody);
	dynamicSteeringOutput dynamicWander(Body* targetBody, Body* charBody);
	static dynamicSteeringOutput dynamicSeparation(std::vector<NPCInterface*> npcVector, Body* charBody);
	static dynamicSteeringOutput dynamicObstacleAvoidance(std::vector<Obstacle*> obstacleVector, Body* charBody);
};

#endif // !DYNAMIC_BEHAVIOUR_H

#ifndef SCENE1_DYNAMIC_BEHAVIOUR_H
#define SCENE1_DYNAMIC_BEHAVIOUR_H

#include "DynamicBehaviour.h"

class Scene1DynamicBehaviour : public DynamicBehaviour
{
public:
	Scene1DynamicBehaviour() {};
	~Scene1DynamicBehaviour() {};

	void Update(Body* targetBody, Body* charBody) override;
	void Update(std::vector<NPCInterface*> npcVector, Body* charBody) override;
	void Update(std::vector<Obstacle*> obstacleVector, Body* charBody) override;
};

#endif // !SCENE1_DYNAMIC_BEHAVIOUR_H

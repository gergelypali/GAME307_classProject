#ifndef STATIC_NPC_H
#define STATIC_NPC_H

#include "NPC.h"
#include "KinematicSteeringOutput.h"

class StaticNPC : public NPC<KinematicSteeringOutput>
{
public:
	StaticNPC(Scene* currentScene, Body* body, SDL_Texture* texture, float scale)
		: NPC(currentScene, body, texture, scale, new KinematicSteeringOutput{}) {};

	void Update(float deltaTime) override;
};

#endif // !STATIC_NPC_H

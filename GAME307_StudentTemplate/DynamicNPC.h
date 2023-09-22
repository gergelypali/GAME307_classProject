#ifndef DYNAMIC_NPC_H
#define DYNAMIC_NPC_H

#include "NPC.h"
#include "DynamicNPCBehaviour.h"

class DynamicNPC : public NPC<DynamicNPCBehaviour>
{
public:
	DynamicNPC(Scene* currentScene, Body* body, SDL_Texture* texture, float scale)
		: NPC(currentScene, body, texture, scale, new DynamicNPCBehaviour{}) {};

	void Update(float deltaTime) override;
};

#endif // !DYNAMIC_NPC_H

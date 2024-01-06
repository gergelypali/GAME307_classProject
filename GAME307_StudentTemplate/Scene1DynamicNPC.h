#ifndef SCENE1_DYNAMIC_NPC_H
#define SCENE1_DYNAMIC_NPC_H

#include "NPC.h"
#include "Scene1DynamicBehaviour.h"

class Scene1DynamicNPC : public NPC<Scene1DynamicBehaviour>
{
public:
	Scene1DynamicNPC(Scene* currentScene, Body* body, SDL_Texture* texture, float scale)
		: NPC(currentScene, body, texture, scale, new Scene1DynamicBehaviour{}) {};
};

#endif // !SCENE1_DYNAMIC_NPC_H

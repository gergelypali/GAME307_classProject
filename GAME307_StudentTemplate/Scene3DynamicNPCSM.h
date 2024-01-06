#ifndef SCENE3_DYNAMIC_NPC_SM_H
#define SCENE3_DYNAMIC_NPC_SM_H

#include "NPC.h"
#include "Scene3DynamicBehaviourSM.h"

class Scene3DynamicNPCSM : public NPC<Scene3DynamicBehaviourSM>
{
public:
	Scene3DynamicNPCSM(Scene* currentScene, Body* body, SDL_Texture* texture, float scale)
		: NPC(currentScene, body, texture, scale, new Scene3DynamicBehaviourSM{}) {};
};

#endif // !SCENE3_DYNAMIC_NPC_SM_H

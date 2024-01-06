#ifndef SCENE3_DYNAMIC_NPC_TREE_H
#define SCENE3_DYNAMIC_NPC_TREE_H

#include "NPC.h"
#include "Scene3DynamicBehaviourTree.h"

class Scene3DynamicNPCTree : public NPC<Scene3DynamicBehaviourTree>
{
public:
	Scene3DynamicNPCTree(Scene* currentScene, Body* body, SDL_Texture* texture, float scale)
		: NPC(currentScene, body, texture, scale, new Scene3DynamicBehaviourTree{}) {};
};

#endif // !SCENE3_DYNAMIC_NPC_TREE_H

#ifndef SCENE3_DYNAMIC_BEHAVIOUR_TREE_H
#define SCENE3_DYNAMIC_BEHAVIOUR_TREE_H

#include "npcDecisionTree.h"
#include "DynamicBehaviour.h"

class Scene3DynamicBehaviourTree : public DynamicBehaviour
{
public:
	Scene3DynamicBehaviourTree() {
		tree = new dynamicDecisionTree();
	};
	~Scene3DynamicBehaviourTree() {
		delete tree;
	};

	void Update(Body* targetBody, Body* charBody) override;
	void Update(std::vector<NPCInterface*> npcVector, Body* charBody) override {};
	void Update(std::vector<Obstacle*> obstacleVector, Body* charBody) override {};

	dynamicDecisionTree* tree{ nullptr };
};

#endif // !SCENE3_DYNAMIC_BEHAVIOUR_TREE_H

#ifndef DYNAMIC_NPC_BEHAVIOUR_H
#define DYNAMIC_NPC_BEHAVIOUR_H

#include "npcDecisionTree.h"
#include "npcStateMachine.h"
#include "DynamicBehaviour.h"

class DynamicNPCBehaviour : public DynamicBehaviour
{
public:
	DynamicNPCBehaviour() {
		tree = new dynamicDecisionTree();
		stateM = new npcStateMachine();
	};
	~DynamicNPCBehaviour()
	{
		delete tree;
		delete stateM;
	}

	void Update(Body* targetBody, Body* charBody) override;
	void Update(std::vector<NPCInterface*> npcVector, Body* charBody) override;
	void Update(std::vector<Obstacle*> obstacleVector, Body* charBody) override;

	dynamicDecisionTree* tree{ nullptr };
	npcStateMachine* stateM{ nullptr };
};

#endif // !DYNAMIC_NPC_BEHAVIOUR_H

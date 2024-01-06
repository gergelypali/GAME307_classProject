#ifndef SCENE3_DYNAMIC_BEHAVIOUR_SM_H
#define SCENE3_DYNAMIC_BEHAVIOUR_SM_H

#include "npcStateMachine.h"
#include "DynamicBehaviour.h"

class Scene3DynamicBehaviourSM : public DynamicBehaviour
{
public:
	Scene3DynamicBehaviourSM() {
		stateM = new npcStateMachine();
	};
	~Scene3DynamicBehaviourSM() {
		delete stateM;
	};

	void Update(Body* targetBody, Body* charBody) override;
	void Update(std::vector<NPCInterface*> npcVector, Body* charBody) override {};
	void Update(std::vector<Obstacle*> obstacleVector, Body* charBody) override {};

	npcStateMachine* stateM{ nullptr };
};

#endif // !SCENE3_DYNAMIC_BEHAVIOUR_SM_H

#ifndef NPC_STATE_MACHINE_H
#define NPC_STATE_MACHINE_H

#include "StateMachine.h"

class seekToVelMatchCond : public floatCondition
{
public:
	Body* targetB{ nullptr };
	Body* ownB{ nullptr };

	float testValue() override
	{
		std::cout << "In Seek state" << std::endl;
		return MATH::VMath::mag(targetB->getPos() - ownB->getPos());
	}
};

class velMatchToFaceCond : public floatCondition
{
public:
	Body* targetB{ nullptr };

	float testValue() override
	{
		std::cout << "In VelMatch state" << std::endl;
		return MATH::VMath::mag(targetB->getVel());
	}
};

class faceToSeekCond : public floatCondition
{
public:
	Body* targetB{ nullptr };

	float testValue() override
	{
		std::cout << "In Face state" << std::endl;
		return targetB->getOrientation();
	}
};

class npcStateMachine : public StateMachine
{
public:
	npcStateMachine()
	{
		Setup();
	};
	~npcStateMachine()
	{
		delete seekToVelocityMatchCondition;
		delete seekToVelocityMatchTransition;
		delete actionVelocityMatch;
		delete actionSeek;
		delete stateVelocityMatch;
		delete stateSeek;
		delete actionFace;
		delete velMatchToFaceCondition;
		delete velMatchToFaceTransition;
		delete stateFace;
		delete faceToSeekCondition;
		delete faceToSeekTransition;
	}

	dynamicSteeringOutput Update(Body* targetB, Body* ownB)
	{
		seekToVelocityMatchCondition->targetB = targetB;
		seekToVelocityMatchCondition->ownB = ownB;
		velMatchToFaceCondition->targetB = targetB;
		faceToSeekCondition->targetB = targetB;
		return StateMachine::Update()->doAction(targetB, ownB);
	}

private:
	State* stateSeek = new State();
	State* stateVelocityMatch = new State();
	State* stateFace = new State();

	stateAction* actionSeek = new stateAction(DynamicBehaviour::dynamicSeek);
	seekToVelMatchCond* seekToVelocityMatchCondition = new seekToVelMatchCond();
	Transition* seekToVelocityMatchTransition = new Transition(stateVelocityMatch, seekToVelocityMatchCondition);

	stateAction* actionVelocityMatch = new stateAction(DynamicBehaviour::dynamicVelocityMatch);
	velMatchToFaceCond* velMatchToFaceCondition = new velMatchToFaceCond();
	Transition* velMatchToFaceTransition = new Transition(stateFace, velMatchToFaceCondition);
	
	stateAction* actionFace = new stateAction(DynamicBehaviour::dynamicFace);
	faceToSeekCond* faceToSeekCondition = new faceToSeekCond();
	Transition* faceToSeekTransition = new Transition(stateSeek, faceToSeekCondition);

	void Setup()
	{
		setInitState(stateSeek);

		seekToVelocityMatchCondition->minValue = 0.f;
		seekToVelocityMatchCondition->maxValue = 500.f;
		velMatchToFaceCondition->minValue = 20.f;
		velMatchToFaceCondition->maxValue = 200.f;
		faceToSeekCondition->minValue = 10.f;
		faceToSeekCondition->maxValue = 2000.f;

		stateSeek->addAction(actionSeek);
		stateSeek->addTransition(seekToVelocityMatchTransition);
		stateVelocityMatch->addAction(actionVelocityMatch);
		stateVelocityMatch->addTransition(velMatchToFaceTransition);
		stateFace->addAction(actionFace);
		stateFace->addTransition(faceToSeekTransition);
	}

};

#endif // !NPC_STATE_MACHINE_H

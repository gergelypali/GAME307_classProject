#include "DecisionTree.h"
#include "Body.h"
#include "DynamicBehaviour.h"
#include <functional>

class dynamicBehaviourAction : public action
{
public:
	dynamicBehaviourAction(
		std::function<dynamicSteeringOutput(Body*, Body*)> theAction
	) :
		doAction(theAction)
	{};

	std::function<dynamicSteeringOutput(Body*, Body*)> doAction;

};

class targetInRange : public floatDecision {
public:
	Body* targetB{nullptr};
	Body* ownB{nullptr};
	float testValue() override
	{
		return MATH::VMath::mag(targetB->getPos() - ownB->getPos());
	};
};

class velocityInRange : public floatDecision {
public:
	Body* targetB{ nullptr };
	float testValue() override
	{
		return MATH::VMath::mag(targetB->getVel());
	};
};

class dynamicDecisionTree
{
public:
	targetInRange* m_targetInRange{ nullptr };
	velocityInRange* m_velocityInRange{ nullptr };
	dynamicBehaviourAction* m_seekAction{ nullptr };
	dynamicBehaviourAction* m_faceAction{ nullptr };
	dynamicBehaviourAction* m_vMatchAction{ nullptr };

	dynamicDecisionTree()
	{
		m_targetInRange = new targetInRange();
		m_velocityInRange = new velocityInRange();
		m_seekAction = new dynamicBehaviourAction(DynamicBehaviour::dynamicSeek);
		m_faceAction = new dynamicBehaviourAction(DynamicBehaviour::dynamicFace);
		m_vMatchAction = new dynamicBehaviourAction(DynamicBehaviour::dynamicVelocityMatch);
		m_targetInRange->minValue = 100.f;
		m_targetInRange->maxValue = 20000.f;
		m_targetInRange->trueNode = m_seekAction;
		m_targetInRange->falseNode = m_vMatchAction;
		m_velocityInRange->minValue = 0.f;
		m_velocityInRange->maxValue = 20000.f;
		m_velocityInRange->trueNode = m_faceAction;
		m_velocityInRange->falseNode = m_targetInRange;
	}
	~dynamicDecisionTree()
	{
		delete m_targetInRange;
		delete m_velocityInRange;
		delete m_seekAction;
		delete m_faceAction;
		delete m_vMatchAction;
	}
	dynamicSteeringOutput makeDecision(Body* targetB, Body* charB)
	{
		m_targetInRange->targetB = targetB;
		m_targetInRange->ownB = charB;
		m_velocityInRange->targetB = targetB;
		return dynamic_cast<dynamicBehaviourAction*>(m_velocityInRange->makeDecision())->doAction(targetB, charB);
	};

};

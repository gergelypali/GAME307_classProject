#ifndef STATE_H
#define STATE_H

#include "Body.h"
#include "DynamicBehaviour.h"
#include <functional>

class Transition;

class stateAction
{
public:
	std::function<dynamicSteeringOutput(Body*, Body*)> doAction;

	stateAction(
		std::function<dynamicSteeringOutput(Body*, Body*)> theAction
	) :
		doAction(theAction)
	{};
};

class Condition
{
public:
	virtual bool test() = 0;

};

class State
{
public:
	std::vector<stateAction*> getActions() { return actions; };
	void addAction(stateAction* newAction) { actions.push_back(newAction); };
	std::vector<Transition*> getTransitions() { return transitions; };
	void addTransition(Transition* newTransition) { transitions.push_back(newTransition); };

private:
	std::vector<stateAction*> actions{};
	std::vector<Transition*> transitions{};

};

class Transition
{
public:
	Transition(State* newState, Condition* newCondition) :
		targetState(newState),
		condition(newCondition)
	{};

	State* getTargetState() { return targetState; };
	bool isTriggered() { return condition->test(); };

private:
	State* targetState{ nullptr };
	Condition* condition{ nullptr };

};

class boolCondition : public Condition
{
public:
	virtual bool testValue() = 0;

	bool test() override
	{
		return testValue();
	};
};

class floatCondition : public Condition
{
public:
	float minValue{};
	float maxValue{};
	virtual float testValue() = 0;

	bool test() override
	{
		if (maxValue >= testValue() && testValue() > minValue)
			return true;
		else
			return false;
	};
};

class andCondition : public Condition
{
public:
	andCondition(Condition* a, Condition* b) :
		conditionA(a),
		conditionB(b)
	{};

	Condition* conditionA{ nullptr };
	Condition* conditionB{ nullptr };

	bool test() override
	{
		return conditionA->test() && conditionB->test();
	}
};

class orCondition : public Condition
{
public:
	orCondition(Condition* a, Condition* b) :
		conditionA(a),
		conditionB(b)
	{};

	Condition* conditionA{ nullptr };
	Condition* conditionB{ nullptr };

	bool test() override
	{
		return conditionA->test() || conditionB->test();
	}
};

class noCondition : public Condition
{
public:
	noCondition(Condition* conD) :
		condition(conD)
	{};

	Condition* condition{ nullptr };

	bool test() override
	{
		return !condition->test();
	}
};

#endif // !STATE_H

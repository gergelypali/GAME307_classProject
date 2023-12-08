#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"

class StateMachine
{
public:
	StateMachine(){};

	void setInitState(State* newInitState) {
		initialState = newInitState;
		currentState = newInitState;
	};

	stateAction* Update()
	{
		Transition* triggeredOne{ nullptr };

		for (auto const& i : currentState->getTransitions())
		{
			if (i->isTriggered())
			{
				triggeredOne = i;
				break;
			}
		}

		if (triggeredOne)
		{
			std::vector<stateAction*> actions{};
			State* targetState = triggeredOne->getTargetState();
			auto toInsert = targetState->getActions();
			actions.insert(actions.end(), toInsert.begin(), toInsert.end());

			currentState = targetState;
			return actions[0];
		}
		else
			return currentState->getActions()[0];
	}

private:
	State* initialState{ nullptr };
	State* currentState{ nullptr };

};

#endif
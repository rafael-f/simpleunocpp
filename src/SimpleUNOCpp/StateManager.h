#pragma once
#include <vector>
#include <memory>
#include "State.h"

class StateManager
{
public:
	StateManager();

	void Draw(Window& window);

	void setState(const int& stateIndex);

private:
	std::vector<std::unique_ptr<State>> _states;

	void initializeStates();

	int _currentState;
};

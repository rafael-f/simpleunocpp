#pragma once
#include <vector>
#include <memory>
#include "State.h"
#include "InputManager.h"
#include "ChangeStateEvent.h"

class StateManager
{
public:
	StateManager();

	void Draw();

	void setState(const int& stateIndex);

	void handleInput();

private:
	std::vector<std::unique_ptr<State>> _states;

	std::unique_ptr<InputManager> _inputManager;

	void initializeStates();

	int _currentState;

	void handleChangeStateEvent(const ChangeStateEvent& changeStateEvent);
};

#pragma once
#include <vector>
#include <memory>
#include "State.h"
#include "GoToNextStateEvent.h"

// Manages states, forwards draw and input to the current state.
class StateManager
{
public:
	StateManager();

	void Draw(const Window& window);

	void setState(const int& stateIndex, const std::shared_ptr<TransitionData> transitionData);

	void handleInput();

private:
	std::vector<std::unique_ptr<State>> _states;

	void initializeStates();

	int _currentState;

	void handleGoToNextStateEvent(const GoToNextStateEvent& goToNextStateEvent);
};

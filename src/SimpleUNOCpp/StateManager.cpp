#include "StateManager.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"
#include "Mediator.h"
#include "PlayerSelectState.h"

StateManager::StateManager()
{
	initializeStates();

	Mediator::registerListener<GoToNextStateEvent>([this](const GoToNextStateEvent& eventData)
	{
		handleChangeStateEvent(eventData);
	});
}

void StateManager::setState(const int& stateIndex)
{
	_currentState = stateIndex;
}

void StateManager::initializeStates()
{
	_states.push_back(std::make_unique<MenuState>());
	_states.push_back(std::make_unique<PlayerSelectState>());
	_states.push_back(std::make_unique<GameState>());
	_states.push_back(std::make_unique<GameOverState>());
}

void StateManager::Draw()
{
	_states[_currentState]->draw();
}

void StateManager::handleInput()
{
	_states[_currentState]->handleInput();
}

// Example usage
void StateManager::handleChangeStateEvent(const GoToNextStateEvent&)
{
	int nextState = _currentState + 1;

	if (nextState >= _states.size())
	{
		nextState = 0;
	}

	setState(nextState);
}

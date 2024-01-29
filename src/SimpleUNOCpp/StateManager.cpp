#include "StateManager.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"
#include "Mediator.h"
#include "PlayerSelectState.h"
#include "PlayerNamesState.h"

StateManager::StateManager()
{
	initializeStates();

	Mediator::registerListener<GoToNextStateEvent>([this](const GoToNextStateEvent& eventData)
	{
		handleGoToNextStateEvent(eventData);
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
	_states.push_back(std::make_unique<PlayerNamesState>());
	_states.push_back(std::make_unique<GameState>());
	_states.push_back(std::make_unique<GameOverState>());
}

void StateManager::Draw(const Window& window)
{
	_states[_currentState]->draw(window);
}

void StateManager::handleInput()
{
	_states[_currentState]->handleInput();
}

void StateManager::handleGoToNextStateEvent(const GoToNextStateEvent&)
{
	int nextState = _currentState + 1;

	if (nextState >= _states.size())
	{
		nextState = 0;
	}

	setState(nextState);
}

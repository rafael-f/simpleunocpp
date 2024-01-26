#include "StateManager.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"

StateManager::StateManager()
{
	initializeStates();
}

void StateManager::setState(const int& stateIndex)
{
	_currentState = stateIndex;
}

void StateManager::initializeStates()
{
	_states.push_back(std::make_unique<MenuState>());
	_states.push_back(std::make_unique<GameState>());
	_states.push_back(std::make_unique<GameOverState>());
}

void StateManager::Draw(Window& window)
{
	_states[_currentState]->draw(window);
}

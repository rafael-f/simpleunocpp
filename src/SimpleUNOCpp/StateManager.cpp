#include "StateManager.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"
#include "Mediator.h"

StateManager::StateManager()
{
	initializeStates();

	_inputManager = std::make_unique<InputManager>();

	Mediator::registerListener<ChangeStateEvent>([this](const ChangeStateEvent & eventData)
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
	_states.push_back(std::make_unique<GameState>());
	_states.push_back(std::make_unique<GameOverState>());
}

void StateManager::Draw()
{
	_states[_currentState]->draw();
}

void StateManager::handleInput()
{
	std::string inputString = _inputManager->handleInput();
	_states[_currentState]->handleInput(inputString);
}

// Example usage
void StateManager::handleChangeStateEvent(const ChangeStateEvent& event) {
	setState(event.nextState);
}

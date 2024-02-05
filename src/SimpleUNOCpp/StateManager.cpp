#include "StateManager.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"
#include "EventBus.h"
#include "PlayerSelectState.h"
#include "PlayerNamesState.h"
#include "TransitionData.h"
#include "GoToFirstStateEvent.h"

StateManager::StateManager()
{
	initializeStates();

	EventBus::registerListener<GoToNextStateEvent>([this](const GoToNextStateEvent& eventData)
	{
		handleGoToNextStateEvent(eventData);
	});

	EventBus::registerListener<GoToFirstStateEvent>([this](const GoToFirstStateEvent& eventData)
	{
		handleGoToFirstStateEvent();
	});
}

void StateManager::setState(const int& stateIndex, const std::shared_ptr<TransitionData> transitionData)
{
	if (stateIndex > -1 && stateIndex < _states.size())
	{
		_currentState = stateIndex;
		_states[_currentState]->setData(transitionData);
	}
}

void StateManager::initializeStates()
{
	_states.push_back(std::make_unique<MenuState>());
	_states.push_back(std::make_unique<PlayerSelectState>());
	_states.push_back(std::make_unique<PlayerNamesState>());
	_states.push_back(std::make_unique<GameState>());
	_states.push_back(std::make_unique<GameOverState>());
}

void StateManager::Draw(Window& window)
{
	_states[_currentState]->draw(window);
}

void StateManager::handleInput()
{
	_states[_currentState]->handleInput();
}

void StateManager::handleGoToNextStateEvent(const GoToNextStateEvent& goToNextStateEvent)
{
	int nextState = _currentState + 1;

	if (nextState >= _states.size())
	{
		nextState = 0;
	}

	setState(nextState, goToNextStateEvent.transitionData);
}

void StateManager::handleGoToFirstStateEvent()
{
	setState(0, nullptr);
}

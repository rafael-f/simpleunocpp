#include "GameState.h"
#include <iostream>
#include "QuitGameEvent.h" // TODO remove?
#include "Mediator.h" // TODO remove?

void GameState::draw(const Window& window)
{
	std::cout << "in game screen" << std::endl;
}

void GameState::handleInput()
{
	// TODO
	QuitGameEvent quitGameEvent; // TODO remove?
	Mediator::fireEvent(quitGameEvent); // TODO remove?
}

void GameState::setData(std::shared_ptr<TransitionData> transitionData)
{

}

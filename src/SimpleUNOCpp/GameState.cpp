#include "GameState.h"
#include <iostream>
#include "QuitGameEvent.h"
#include "Mediator.h"

void GameState::draw()
{
	std::cout << "in game screen" << std::endl;
}

void GameState::handleInput()
{
	// TODO
	QuitGameEvent quitGameEvent;
	Mediator::fireEvent(quitGameEvent);
}

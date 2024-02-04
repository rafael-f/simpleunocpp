#include "GameOverState.h"
#include "GameOverTransitionData.h"
#include <iostream>
#include <conio.h>
#include "KeyCodes.h"
#include "Mediator.h"
#include "GoToFirstStateEvent.h"

void GameOverState::draw(Window& window)
{
	std::cout << "Winner is " << _winnerName << std::endl;
	std::cout << "Press ENTER to restart.";
}

void GameOverState::handleInput()
{
	int input = _getch();

	if (input == KeyCodes::ENTER_KEY)
	{
		Mediator::fireEvent(GoToFirstStateEvent());
	}
}

void GameOverState::setData(std::shared_ptr<TransitionData> transitionData)
{
	std::shared_ptr<GameOverTransitionData> data = std::dynamic_pointer_cast<GameOverTransitionData>(transitionData);
	_winnerName = data->_winnerName;
}

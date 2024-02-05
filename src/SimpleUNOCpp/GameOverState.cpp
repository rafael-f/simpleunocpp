#include "GameOverState.h"
#include "GameOverTransitionData.h"
#include <iostream>
#include <conio.h>
#include "KeyCodes.h"
#include "EventBus.h"
#include "GoToFirstStateEvent.h"

void GameOverState::draw(Window& window)
{
	std::cout << "Winner is " << _winnerName << std::endl;
	std::cout << "Press ENTER to restart or ESC to quit.";
}

void GameOverState::handleInput()
{
	int input = _getch();

	if (input == KeyCodes::ENTER_KEY)
	{
		EventBus::fireEvent(GoToFirstStateEvent());
	}
	else if (input == KeyCodes::ESCAPE_KEY)
	{
		EventBus::fireEvent(QuitGameEvent());
	}
}

void GameOverState::setData(std::shared_ptr<TransitionData> transitionData)
{
	std::shared_ptr<GameOverTransitionData> data = std::dynamic_pointer_cast<GameOverTransitionData>(transitionData);
	_winnerName = data->_winnerName;
}

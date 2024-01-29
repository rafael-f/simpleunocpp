#include "PlayerNamesState.h"
#include <conio.h>
#include "Mediator.h"
#include "QuitGameEvent.h"
#include <iostream>
#include "PlayerSelectedAmountTransitionData.h"

void PlayerNamesState::draw(const Window& window)
{
	std::cout << "Players: " << _numberOfPlayers << std::endl;
	std::cout << "Press ESC to quit" << std::endl;
}

void PlayerNamesState::handleInput()
{
	int input = _getch();
	if (input == 27)
	{
		QuitGameEvent quitGameEvent;
		Mediator::fireEvent(quitGameEvent);
	}
}

void PlayerNamesState::setData(std::shared_ptr<TransitionData> transitionData)
{
	std::shared_ptr<PlayerSelectedAmountTransitionData> data = std::dynamic_pointer_cast<PlayerSelectedAmountTransitionData>(transitionData);
	_numberOfPlayers = data->selectedAmount;
}

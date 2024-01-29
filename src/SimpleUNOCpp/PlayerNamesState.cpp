#include "PlayerNamesState.h"
#include <conio.h>
#include "Mediator.h"
#include "QuitGameEvent.h"
#include <iostream>

void PlayerNamesState::draw(const Window& window)
{
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

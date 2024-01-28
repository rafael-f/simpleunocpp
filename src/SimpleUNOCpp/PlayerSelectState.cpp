#include "PlayerSelectState.h"
#include <iostream>
#include "QuitGameEvent.h"
#include "Mediator.h"
#include <conio.h>
#include "GoToNextStateEvent.h"

const std::string PlayerSelectState::AMOUNT_OF_PLAYERS_QUESTION = "How many players will participate?";

PlayerSelectState::PlayerSelectState()
{
	for (int i = MIN_AMOUNT; i < MAX_AMOUNT + 1; ++i)
	{
		_options.push_back(std::make_unique<PlayersOption>(i));
	}

	_options[0]->setSelected(true);
}

void PlayerSelectState::draw()
{
	std::cout << AMOUNT_OF_PLAYERS_QUESTION << std::endl;

	int startRow = 3;
	int startColumn = 0;

	for (int i = 0; i < _options.size(); ++i)
	{
		_options[i]->draw(startRow, startColumn);
		startColumn += _options[i]->getLength() + 2;
	}
}

void PlayerSelectState::handleInput()
{
	int input = _getch();

	if (input == 27)
	{
		QuitGameEvent quitGameEvent;
		Mediator::fireEvent(quitGameEvent);
	}
	else if (input == 13)
	{
		GoToNextStateEvent goToNextState;
		Mediator::fireEvent(goToNextState);
	}
	else if (input == 0 || input == 224)
	{
		input = _getch();

		switch (input)
		{
		case 75:
			selectPreviousOption();
			break;
		case 77:
			selectNextOption();
			break;
		}
	}
}

void PlayerSelectState::selectPreviousOption()
{
	_options[_selectedIndex]->setSelected(false);

	if (_selectedIndex == 0)
	{
		_selectedIndex = _options.size() - 1;
	}
	else
	{
		--_selectedIndex;
	}

	_options[_selectedIndex]->setSelected(true);
}

void PlayerSelectState::selectNextOption()
{
	_options[_selectedIndex]->setSelected(false);

	if (_selectedIndex == _options.size() - 1)
	{
		_selectedIndex = 0;
	}
	else
	{
		++_selectedIndex;
	}

	_options[_selectedIndex]->setSelected(true);
}

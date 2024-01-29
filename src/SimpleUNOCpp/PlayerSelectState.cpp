#include "PlayerSelectState.h"
#include <iostream>
#include "QuitGameEvent.h"
#include "Mediator.h"
#include <conio.h>
#include "GoToNextStateEvent.h"
#include "KeyCodes.h"
#include "PlayerSelectedAmountTransitionData.h"

const std::string PlayerSelectState::AMOUNT_OF_PLAYERS_QUESTION = "How many players will participate?";

PlayerSelectState::PlayerSelectState()
{
	for (int i = MIN_AMOUNT; i < MAX_AMOUNT + 1; ++i)
	{
		_options.push_back(std::make_unique<PlayersOption>(i));
	}

	_options[0]->setSelected(true);
}

void PlayerSelectState::draw(Window& window)
{
	std::cout << AMOUNT_OF_PLAYERS_QUESTION << std::endl;

	int startRow = 3;
	int startColumn = 0;

	for (int i = 0; i < _options.size(); ++i)
	{
		_options[i]->draw(window, startRow, startColumn);
		startColumn += _options[i]->getLength() + 2;
	}
}

void PlayerSelectState::handleInput()
{
	int input = _getch();

	if (input == KeyCodes::ESCAPE_KEY)
	{
		QuitGameEvent quitGameEvent;
		Mediator::fireEvent(quitGameEvent);
	}
	else if (input == KeyCodes::ENTER_KEY)
	{
		int playersAmount = _options[_selectedIndex]->getValue();

		GoToNextStateEvent goToNextState;
		goToNextState.transitionData = std::make_unique<PlayerSelectedAmountTransitionData>(playersAmount);
		Mediator::fireEvent(goToNextState);
	}
	else if (input == KeyCodes::ARROW_1 || input == KeyCodes::ARROW_2)
	{
		input = _getch();

		switch (input)
		{
		case KeyCodes::LEFT_ARROW:
			selectPreviousOption();
			break;
		case KeyCodes::RIGHT_ARROW:
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
		_selectedIndex = static_cast<int>(_options.size()) - 1;
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

void PlayerSelectState::setData(std::shared_ptr<TransitionData>)
{
}

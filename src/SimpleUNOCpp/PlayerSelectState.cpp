#include "PlayerSelectState.h"
#include <iostream>
#include "QuitGameEvent.h"
#include "Mediator.h"

const std::string PlayerSelectState::AMOUNT_OF_PLAYERS_QUESTION = "How many players will participate?";

PlayerSelectState::PlayerSelectState()
{
	for (int i = MIN_AMOUNT; i < MAX_AMOUNT; ++i)
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
		//std::cout << _options[i]->getValue() << std::endl;
		_options[i]->draw(startRow, startColumn);
		startColumn += 4;
	}
}

void PlayerSelectState::handleInput()
{
	QuitGameEvent quitGameEvent;
	Mediator::fireEvent(quitGameEvent);
}

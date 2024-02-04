#include <conio.h>
#include <iostream>
#include "PlayerNamesState.h"
#include "GoToNextStateEvent.h"
#include "KeyCodes.h"
#include "Mediator.h"
#include "PlayerManagerTransitionData.h"
#include "PlayerSelectedAmountTransitionData.h"
#include "QuitGameEvent.h"
#include "ShowPromptEvent.h"

void PlayerNamesState::draw(Window& window)
{
	window.showPrompt(true);

	std::cout << "Type the names of every player (names must be unique and between 1 and 10 characters): " << std::endl << std::endl;

	int editingLineLength;

	for (int i = 0; i < _numberOfPlayers; ++i)
	{
		if (i < _currentPlayerEditingIndex)
		{
			std::cout << "Player " << (i + 1) << ": " << _playerManager->getPlayer(i)->getName() << std::endl;
		}
		else
		{
			std::string line = "Player " + std::to_string(i + 1) + ": ";

			if (i == _currentPlayerEditingIndex)
			{
				line += _currentEditingName;

				editingLineLength = static_cast<int>(line.length());
			}

			std::cout << line << std::endl;
		}
	}

	window.setCursorPosition(_currentPlayerEditingIndex + 2, editingLineLength);
}

void PlayerNamesState::handleInput()
{
	int input = _getch();
	if (input == KeyCodes::ESCAPE_KEY)
	{
		QuitGameEvent quitGameEvent;
		Mediator::fireEvent(quitGameEvent);
	}
	else if (input == KeyCodes::ENTER_KEY)
	{
		handleEnterKey();
	}
	else if (input == KeyCodes::BACKSPACE)
	{
		if (!_currentEditingName.empty())
		{
			_currentEditingName.pop_back();
		}
	}
	else
	{
		if (_currentEditingName.length() < 10)
		{
			_currentEditingName += static_cast<char>(input);
		}
	}
}

void PlayerNamesState::handleEnterKey()
{
	if (_currentEditingName.length() > 0)
	{
		for (auto player : _playerManager->getPlayers())
		{
			if (player->getName() == _currentEditingName)
			{
				return;
			}
		}

		std::shared_ptr<Player> player = std::make_shared<Player>();
		player->setName(_currentEditingName);
		_playerManager->addPlayer(player);

		_currentEditingName = "";
		++_currentPlayerEditingIndex;

		if (_currentPlayerEditingIndex >= _numberOfPlayers)
		{
			transitionToGame();
		}
	}
}

void PlayerNamesState::setData(std::shared_ptr<TransitionData> transitionData)
{
	std::shared_ptr<PlayerSelectedAmountTransitionData> data = std::dynamic_pointer_cast<PlayerSelectedAmountTransitionData>(transitionData);
	_numberOfPlayers = data->selectedAmount;
	_currentPlayerEditingIndex = 0;
	_currentEditingName = "";

	if (_playerManager)
	{
		_playerManager->clearPlayers();
	}
	else
	{
		_playerManager = std::make_shared<PlayerManager>();
	}
}

void PlayerNamesState::transitionToGame()
{
	ShowPromptEvent showPromptEvent;
	showPromptEvent.showPrompt = false;
	Mediator::fireEvent(showPromptEvent);

	GoToNextStateEvent goToNextStateEvent;
	goToNextStateEvent.transitionData = std::make_shared<PlayerManagerTransitionData>(_playerManager);
	Mediator::fireEvent(goToNextStateEvent);
}

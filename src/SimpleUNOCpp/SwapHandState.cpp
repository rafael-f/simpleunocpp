#include "GameState.h"
#include "Window.h"
#include <iostream>
#include <conio.h>
#include "KeyCodes.h"
#include <algorithm>

void GameState::drawSelectPlayerState(const Window& window) const
{
	window.setCursorPosition(0, 0);
	std::cout << "SELECT A PLAYER TO SWAP HAND WITH:";

	int row = 2;
	int column = 0;
	int maxLength = window.getConsoleLineLength();

	for (std::shared_ptr<Player> player : _availableSwapHandPlayers)
	{
		column += player->draw(window, row, column);
		if (column + 15 >= maxLength)
		{
			row += 4;
			column = 0;
		}
	}
}

void GameState::handleInputSelectPlayerState()
{
	int input = _getch();

	if (input == KeyCodes::ESCAPE_KEY)
	{
		Mediator::fireEvent(QuitGameEvent());
	}
	else if (input == KeyCodes::ARROW_1 || input == KeyCodes::ARROW_2)
	{
		input = _getch();

		switch (input)
		{
		case KeyCodes::LEFT_ARROW: // TODO make a method
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(false);
			--_swapHandSelectedIndex;
			if (_swapHandSelectedIndex < 0)
			{
				_swapHandSelectedIndex = static_cast<int>(_availableSwapHandPlayers.size()) - 1;
			}
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(true);
			break;
		case KeyCodes::RIGHT_ARROW:
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(false);
			++_swapHandSelectedIndex;
			if (_swapHandSelectedIndex >= _availableSwapHandPlayers.size())
			{
				_swapHandSelectedIndex = 0;
			}
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(true);
			break;
		}
	}
	else if (input == KeyCodes::ENTER_KEY)
	{
		_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(false);
		_playerManager->getSelectedPlayer()->getCards().swap(_availableSwapHandPlayers[_swapHandSelectedIndex]->getCards());
		_currentState = GameStates::NORMAL;

		// TODO rule... if the player swapped hand with another that had 1 card in hand he's supposed to be
		// able to UNO with 1 card?
		if (_playerManager->getSelectedPlayer()->getCards().size() == 1)
		{
			_playerManager->getSelectedPlayer()->setCanSayUNO(true);
		}

		if (_availableSwapHandPlayers[_swapHandSelectedIndex]->getCards().size() == 1)
		{
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setCanSayUNO(true);
		}

		_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
	}
}

void GameState::handleSwapHandCardEvent()
{
	_currentState = GameStates::SELECT_PLAYER;

	_availableSwapHandPlayers.clear();

	for (std::shared_ptr<Player> player : _playerManager->getPlayers())
	{
		if (player->getName() == _playerManager->getSelectedPlayer()->getName())
		{
			continue;
		}

		_availableSwapHandPlayers.push_back(player);
	}

	_availableSwapHandPlayers[0]->setSelected(true);
	_swapHandSelectedIndex = 0;
}

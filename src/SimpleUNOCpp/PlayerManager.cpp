#include <iostream>
#include "PlayerManager.h"
#include "KeyCodes.h"
#include "VectorHelper.h"

void PlayerManager::clearPlayers()
{
	_players.clear();
}

std::shared_ptr<Player> PlayerManager::getPlayer(const int& index) const
{
	if (index > -1 && index < _players.size())
	{
		return _players[index];
	}

	return nullptr;
}

void PlayerManager::addPlayer(std::shared_ptr<Player> player)
{
	_players.push_back(player);
}

std::vector<std::shared_ptr<Player>>& PlayerManager::getPlayers()
{
	return _players;
}

void PlayerManager::shufflePlayers()
{
	VectorHelper::shuffleVector(_players);
}

void PlayerManager::updatePlayerState(const int& playerIndex, std::shared_ptr<Card> cardOnTop)
{
	_players[_selectedPlayerIndex]->setSelected(false);
	_selectedPlayerIndex = playerIndex;
	_players[_selectedPlayerIndex]->setSelected(true);
	_players[_selectedPlayerIndex]->updateCardStates(cardOnTop);
	_players[_selectedPlayerIndex]->setSelectedCard(0);
}

int PlayerManager::drawPlayersHeader(Window& window, const int& turnDirection) const
{
	std::cout << "PLAYERS:" << std::endl;

	char arrow;
	if (turnDirection == 1)
	{
		arrow = KeyCodes::RIGHT_DOUBLE_ARROW;
	}
	else
	{
		arrow = KeyCodes::LEFT_DOUBLE_ARROW;
	}

	int row = 1;
	int column = 0;

	int maxLength = window.getConsoleLineLength();

	drawArrow(window, arrow, row, column);

	for (std::shared_ptr<Player> player : _players)
	{
		column += player->draw(window, row, column);
		drawArrow(window, arrow, row, column);

		if (column + 15 >= maxLength)
		{
			row += 4;
			column = 0;
		}
	}

	return row + 3;
}

void PlayerManager::drawArrow(Window& window, const char& arrow, const int& row, int& column) const
{
	window.setCursorPosition(row + 1, column);
	std::cout << " " << arrow;
	column += 3;
}

std::shared_ptr<Player> PlayerManager::getSelectedPlayer() const
{
	return getPlayer(_selectedPlayerIndex);
}

void PlayerManager::drawPlayerCards(Window& window, int& row) const
{
	getSelectedPlayer()->drawCards(window, row);
}

void PlayerManager::selectNextPlayer(const int& offset, std::shared_ptr<Card> cardOnTop)
{
	_players[_selectedPlayerIndex]->setSelected(false);

	_selectedPlayerIndex += offset;

	if (_selectedPlayerIndex < 0)
	{
		_selectedPlayerIndex = static_cast<int>(_players.size()) - 1;
	}
	else if (_selectedPlayerIndex >= _players.size())
	{
		_selectedPlayerIndex = 0;
	}

	_players[_selectedPlayerIndex]->setSelected(true);

	updatePlayerState(_selectedPlayerIndex, cardOnTop);
}

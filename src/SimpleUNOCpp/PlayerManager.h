#pragma once
#include <vector>
#include "Player.h"
#include <memory>

// Keeps track of all players.
class PlayerManager
{
public:
	void clearPlayers();

	void addPlayer(std::shared_ptr<Player> player);

	std::shared_ptr<Player> getPlayer(const int& index) const;

	std::vector<std::shared_ptr<Player>>& getPlayers();

	void shufflePlayers();

	void updatePlayerState(const int& playerIndex, std::shared_ptr<Card> cardOnTop);

	std::shared_ptr<Player> getSelectedPlayer() const;

	int drawPlayersHeader(Window& window, const int& turnDirection) const;

	void drawArrow(Window& window, const char& arrow, const int& row, int& column) const;

	void drawPlayerCards(Window& window, int& row) const;

	void selectNextPlayer(const int& offset, std::shared_ptr<Card> cardOnTop);

private:
	std::vector<std::shared_ptr<Player>> _players;

	int _selectedPlayerIndex = 0;
};

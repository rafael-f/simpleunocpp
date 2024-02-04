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

	void updatePlayerState(const int& playerIndex, const Colors& color);

	std::shared_ptr<Player> getSelectedPlayer() const;

	int drawPlayersHeader(Window& window, const int& turnDirection) const;

	void drawArrow(const Window& window, const char& arrow, const int& row, int& column) const;

	void drawPlayerCards(const Window& window, int& row) const;

	void selectNextPlayer(const int& offset, std::shared_ptr<Card> cardOnTop);

	void selectNextPlayer(const int& offset, const Colors& color);

private:
	std::vector<std::shared_ptr<Player>> _players;

	int _selectedPlayerIndex = 0;
};

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

	std::vector<std::shared_ptr<Player>>& getplayers();

private:
	std::vector<std::shared_ptr<Player>> _players;
};

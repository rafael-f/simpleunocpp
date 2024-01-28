#pragma once
#include <vector>
#include "Player.h"

// Keeps track of all players.
class PlayerManager
{
private:
	std::vector<std::shared_ptr<Player>> _players;
};

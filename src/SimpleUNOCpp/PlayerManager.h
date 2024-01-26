#pragma once
#include <vector>
#include "Player.h"

class PlayerManager
{
private:
	std::vector<std::shared_ptr<Player>> _players;
};

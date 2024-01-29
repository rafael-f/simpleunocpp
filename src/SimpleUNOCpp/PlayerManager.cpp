#include "PlayerManager.h"

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

std::vector<std::shared_ptr<Player>>& PlayerManager::getplayers()
{
	return _players;
}

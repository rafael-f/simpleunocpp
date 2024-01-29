#include "Player.h"

void Player::setName(const std::string& name)
{
	_name = name;
}

std::string Player::getName() const
{
	return _name;
}

void Player::updateCardStates(const Card& cardOnTop)
{

}

#pragma once
#include <string>
#include "Card.h"
#include <vector>

// Keeps player name and cards.
class Player
{
public:
	void setName(const std::string& name);

	std::string getName() const;

	void updateCardStates(const Card& cardOnTop);

private:
	std::string _name;

	std::vector<std::shared_ptr<Card>> _cardsOnHand;
};

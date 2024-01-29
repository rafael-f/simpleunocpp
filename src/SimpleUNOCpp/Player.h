#pragma once
#include <string>
#include <vector>
#include "Card.h"

// Keeps player name and cards.
class Player
{
public:
	void setName(const std::string& name);

	std::string getName() const;

	void updateCardStates(const Card& cardOnTop);

	void addCard(std::shared_ptr<Card> card);

	int draw(Window& window, const int& row, const int& column) const;

	void setSelected(const bool& selected);

	void drawCards(Window& window, const int& row) const;

private:
	std::string _name;

	std::vector<std::shared_ptr<Card>> _cardsOnHand;

	int _nameLength;

	bool _isSelected = false;
};

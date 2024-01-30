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

	void updateCardStates(std::shared_ptr<Card> cardOnTop) const;

	void updateCardStates(const Colors& color) const;

	void addCard(std::shared_ptr<Card> card);

	int draw(Window& window, const int& row, const int& column) const;

	void setSelected(const bool& selected);

	void drawCards(Window& window, int& row) const;

	void setSelectedCard(const int& index);

	void selectCard(const int& offset);

private:
	std::string _name;

	std::vector<std::shared_ptr<Card>> _cardsOnHand;

	int _nameLength;

	bool _isSelected = false;

	int _selectedCardIndex = 0;
};

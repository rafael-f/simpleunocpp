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

	void removeSelectedCard();

	int draw(Window& window, const int& row, const int& column) const;

	void setSelected(const bool& selected);

	void drawCards(Window& window, int& row) const;

	void setSelectedCard(const int& index);

	std::shared_ptr<Card> getSelectedCard();

	void selectCard(const int& offset);

	void setSaidUNO(const bool& saidUNO);

private:
	std::string _name;

	std::vector<std::shared_ptr<Card>> _cardsOnHand;

	int _nameLength;

	bool _isSelected = false;

	int _selectedCardIndex = 0;

	bool _saidUNO = false;
};

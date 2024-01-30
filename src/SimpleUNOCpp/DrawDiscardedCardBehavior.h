#pragma once
#include "CardBehavior.h"

// This behavior forces the player to draw cards from the discard pile.
class DrawDiscardedCardBehavior : public CardBehavior
{
public:
	explicit DrawDiscardedCardBehavior(const int& amount);

	void execute() override;

	std::string& getStringToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

private:
	int _amount;

	std::string _stringToDraw;
};

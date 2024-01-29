#pragma once
#include "CardBehavior.h"

// This card will swap the hands of 2 players.
class SwapHandCardBehavior : public CardBehavior
{
public:
	SwapHandCardBehavior();

	void execute() override;

	std::string& getStringToDraw() override;

private:
	std::string _stringToDraw;
};

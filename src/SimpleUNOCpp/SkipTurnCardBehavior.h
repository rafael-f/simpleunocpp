#pragma once
#include "CardBehavior.h"

// This card skips the turn of the next player.
class SkipTurnCardBehavior : public CardBehavior
{
public:
	SkipTurnCardBehavior();

	void execute() override;

	std::string& getStringToDraw();

private:
	std::string _stringToDraw;
};

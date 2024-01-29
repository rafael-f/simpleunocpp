#pragma once
#include "CardBehavior.h"

// This card will reverse the order that players play.
class ReverseTurnCardBehavior : public CardBehavior
{
public:
	ReverseTurnCardBehavior();

	void execute() override;

	std::string& getStringToDraw() override;

private:
	std::string _stringToDraw;
};

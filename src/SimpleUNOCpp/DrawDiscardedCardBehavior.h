#pragma once
#include "CardBehavior.h"

// This behavior forces the player to draw cards from the discard pile.
class DrawDiscardedCardBehavior : public CardBehavior
{
public:
	DrawDiscardedCardBehavior(const int& amount);

private:
	int _amount;
};

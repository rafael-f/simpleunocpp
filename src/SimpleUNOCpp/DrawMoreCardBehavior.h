#pragma once
#include "CardBehavior.h"

// This behavior forces the player to draw more cards from the draw pile.
class DrawMoreCardBehavior : public CardBehavior
{
public:
	explicit DrawMoreCardBehavior(const int& drawMoreAmount);

private:
	int _drawMoreAmount;
};

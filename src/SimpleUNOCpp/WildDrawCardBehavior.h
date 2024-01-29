#pragma once
#include "CardBehavior.h"

class WildDrawCardBehavior : public CardBehavior
{
public:
	explicit WildDrawCardBehavior(const int& drawAmount);

private:
	int _drawAmount;
};

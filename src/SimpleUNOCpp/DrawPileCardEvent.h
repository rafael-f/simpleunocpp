#pragma once
#include "Event.h"

class DrawPileCardEvent : public Event
{
public:
	explicit DrawPileCardEvent(const int& amount);
	
	int getAmount() const;

private:
	int _amount;
};

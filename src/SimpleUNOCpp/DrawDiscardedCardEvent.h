#pragma once
#include "Event.h"

class DrawDiscardedCardEvent : public Event
{
public:
	explicit DrawDiscardedCardEvent(const int& amount);

	int& getAmount();

private:
	int _amount;
};

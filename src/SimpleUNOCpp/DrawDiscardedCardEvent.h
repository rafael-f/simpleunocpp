#pragma once
#include "Event.h"

class DrawDiscardedCardEvent : public Event
{
public:
	explicit DrawDiscardedCardEvent(const int& amount);

	int getAmount() const;

private:
	int _amount;
};

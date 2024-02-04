#pragma once
#include "Event.h"

class WildDrawCardEvent : public Event
{
public:
	explicit WildDrawCardEvent(const int& amount);

	int getAmount() const;

private:
	int _amount;
};

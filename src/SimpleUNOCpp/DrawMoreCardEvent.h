#pragma once
#include "Event.h"

class DrawMoreCardEvent : public Event
{
public:
	explicit DrawMoreCardEvent(const int& amount);

	int& getAmount();

private:
	int _amount;
};

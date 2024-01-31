#pragma once
#include "Event.h"

class DrawDisplayCardEvent : public Event
{
public:
	explicit DrawDisplayCardEvent(const int& amount);
	
	int getAmount() const;

private:
	int _amount;
};

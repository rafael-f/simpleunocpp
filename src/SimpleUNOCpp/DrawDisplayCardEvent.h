#pragma once
#include "Event.h"

class DrawDisplayCardEvent : public Event
{
public:
	explicit DrawDisplayCardEvent(const int& amount);
	
	int& getAmount();

private:
	int _amount;
};

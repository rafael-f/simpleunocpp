#include "WildDrawCardEvent.h"

WildDrawCardEvent::WildDrawCardEvent(const int& amount) : _amount(amount)
{}

int& WildDrawCardEvent::getAmount()
{
	return _amount;
}

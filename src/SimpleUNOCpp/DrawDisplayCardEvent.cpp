#include "DrawDisplayCardEvent.h"

DrawDisplayCardEvent::DrawDisplayCardEvent(const int& amount) : _amount(amount)
{}

int DrawDisplayCardEvent::getAmount() const
{
	return _amount;
}

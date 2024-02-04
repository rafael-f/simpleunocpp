#include "DrawMoreCardEvent.h"

DrawMoreCardEvent::DrawMoreCardEvent(const int& amount) : _amount(amount)
{}

int DrawMoreCardEvent::getAmount() const
{
	return _amount;
}

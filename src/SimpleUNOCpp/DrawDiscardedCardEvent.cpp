#include "DrawDiscardedCardEvent.h"

DrawDiscardedCardEvent::DrawDiscardedCardEvent(const int& amount) : _amount(amount)
{}

int DrawDiscardedCardEvent::getAmount() const
{
	return _amount;
}

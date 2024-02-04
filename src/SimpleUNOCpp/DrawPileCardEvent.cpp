#include "DrawPileCardEvent.h"

DrawPileCardEvent::DrawPileCardEvent(const int& amount) : _amount(amount)
{}

int DrawPileCardEvent::getAmount() const
{
	return _amount;
}

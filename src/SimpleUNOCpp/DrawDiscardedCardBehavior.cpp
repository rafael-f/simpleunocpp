#include "DrawDiscardedCardBehavior.h"

DrawDiscardedCardBehavior::DrawDiscardedCardBehavior(const int& amount) : _amount(amount)
{
	_stringToDraw = "+" + std::to_string(_amount) + "D";
}

void DrawDiscardedCardBehavior::execute()
{
	// TODO
}

std::string& DrawDiscardedCardBehavior::getStringToDraw()
{
	return _stringToDraw; // TODO all behaviors return this string, maybe make CardBehavior abstract?
}

bool DrawDiscardedCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	return true; // This can always be played (color check happens on card level).
}

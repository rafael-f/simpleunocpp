#include "DrawDiscardedCardBehavior.h"

DrawDiscardedCardBehavior::DrawDiscardedCardBehavior(const int& amount) : _amount(amount)
{
	_stringToDraw = "+" + std::to_string(_amount) + "D";
}

void DrawDiscardedCardBehavior::execute()
{

}

std::string& DrawDiscardedCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

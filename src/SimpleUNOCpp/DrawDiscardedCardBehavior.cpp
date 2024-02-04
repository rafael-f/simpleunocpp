#include "DrawDiscardedCardBehavior.h"
#include "DrawDiscardedCardEvent.h"

DrawDiscardedCardBehavior::DrawDiscardedCardBehavior(const int& amount) : _amount(amount)
{
	_symbolToDraw = "+" + std::to_string(_amount) + "D";
}

void DrawDiscardedCardBehavior::execute()
{
	Mediator::fireEvent(DrawDiscardedCardEvent(_amount));
}

std::string& DrawDiscardedCardBehavior::getSymbolToDraw()
{
	return _symbolToDraw;
}

std::string DrawDiscardedCardBehavior::getNameToDraw()
{
	return "";
}

bool DrawDiscardedCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	if (std::shared_ptr<DrawDiscardedCardBehavior> otherCard = std::dynamic_pointer_cast<DrawDiscardedCardBehavior>(otherBehavior))
	{
		return true;
	}

	return false;
}

bool DrawDiscardedCardBehavior::getGoToNextPlayer()
{
	return true;
}
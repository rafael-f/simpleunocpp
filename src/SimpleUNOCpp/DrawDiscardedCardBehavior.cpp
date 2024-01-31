#include "DrawDiscardedCardBehavior.h"
#include "DrawDiscardedCardEvent.h"

DrawDiscardedCardBehavior::DrawDiscardedCardBehavior(const int& amount) : _amount(amount)
{
	_stringToDraw = "+" + std::to_string(_amount) + "D";
}

void DrawDiscardedCardBehavior::execute()
{
	// TODO forces next next player to draw 2 cards from discard pile
	// if not enough cards on discard then draw from the draw pile
	// if discard pile is empty discard one from the draw pile automatically
	Mediator::fireEvent(DrawDiscardedCardEvent(_amount));
}

std::string& DrawDiscardedCardBehavior::getStringToDraw()
{
	return _stringToDraw; // TODO all behaviors return this string, maybe make CardBehavior abstract?
}

bool DrawDiscardedCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	if (std::shared_ptr<DrawDiscardedCardBehavior> otherCard = std::dynamic_pointer_cast<DrawDiscardedCardBehavior>(otherBehavior))
	{
		return true;
	}

	return false;
}

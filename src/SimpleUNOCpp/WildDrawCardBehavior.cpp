#include "WildDrawCardBehavior.h"
#include "WildDrawCardEvent.h"

WildDrawCardBehavior::WildDrawCardBehavior(const int& drawAmount) : _drawAmount(drawAmount)
{
	_symbolToDraw = "+" + std::to_string(drawAmount) + " ";
}

void WildDrawCardBehavior::execute()
{
	Mediator::fireEvent(WildDrawCardEvent(_drawAmount));
}

std::string& WildDrawCardBehavior::getSymbolToDraw()
{
	return _symbolToDraw;
}

bool WildDrawCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	return true;
}

std::string WildDrawCardBehavior::getNameToDraw()
{
	return "";
}

bool WildDrawCardBehavior::getGoToNextPlayer()
{
	return false;
}

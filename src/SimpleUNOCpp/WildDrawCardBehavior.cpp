#include "WildDrawCardBehavior.h"

WildDrawCardBehavior::WildDrawCardBehavior(const int& drawAmount) : _drawAmount(drawAmount)
{
	_symbolToDraw = "+" + std::to_string(drawAmount) + " ";
}

void WildDrawCardBehavior::execute()
{
	// TODO player that plays this card must pick a color
	// forces next player to draw +amount cards, this player has the turn skipped
	// next player has to play a card of the color that was picked
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

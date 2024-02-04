#include "ReverseTurnCardBehavior.h"
#include "KeyCodes.h"
#include "ReverseTurnCardEvent.h"

const std::string ReverseTurnCardBehavior::NAME_TO_DRAW = "REV.";

ReverseTurnCardBehavior::ReverseTurnCardBehavior()
{
	_symbolToDraw = std::string(1, KeyCodes::RIGHT_DOUBLE_ARROW) + " " + std::string(1, KeyCodes::LEFT_DOUBLE_ARROW);
}

void ReverseTurnCardBehavior::execute()
{
	Mediator::fireEvent(ReverseTurnCardEvent());
}

std::string& ReverseTurnCardBehavior::getSymbolToDraw()
{
	return _symbolToDraw;
}

bool ReverseTurnCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	if (std::shared_ptr<ReverseTurnCardBehavior> otherCard = std::dynamic_pointer_cast<ReverseTurnCardBehavior>(otherBehavior))
	{
		return true;
	}

	return false;
}

std::string ReverseTurnCardBehavior::getNameToDraw()
{
	return NAME_TO_DRAW;
}

bool ReverseTurnCardBehavior::getGoToNextPlayer()
{
	return true;
}

#include "SkipTurnCardBehavior.h"
#include "KeyCodes.h"
#include "SkipTurnCardEvent.h"

const std::string SkipTurnCardBehavior::NAME_TO_DRAW = "SKIP";

SkipTurnCardBehavior::SkipTurnCardBehavior()
{
	_symbolToDraw = " " + std::string(1, KeyCodes::SKIP_TURN) + " ";
}

void SkipTurnCardBehavior::execute()
{
	EventBus::fireEvent(SkipTurnCardEvent());
}

std::string& SkipTurnCardBehavior::getSymbolToDraw()
{
	return _symbolToDraw;
}

bool SkipTurnCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	if (std::shared_ptr<SkipTurnCardBehavior> otherCard = std::dynamic_pointer_cast<SkipTurnCardBehavior>(otherBehavior))
	{
		return true;
	}

	return false;
}

std::string SkipTurnCardBehavior::getNameToDraw()
{
	return NAME_TO_DRAW;
}

bool SkipTurnCardBehavior::getGoToNextPlayer()
{
	return true;
}
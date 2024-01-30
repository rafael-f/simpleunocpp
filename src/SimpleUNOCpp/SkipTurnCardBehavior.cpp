#include "SkipTurnCardBehavior.h"
#include "KeyCodes.h"

SkipTurnCardBehavior::SkipTurnCardBehavior()
{
	_stringToDraw = " " + std::string(1, KeyCodes::SKIP_TURN) + " "; // TODO is this bad?
}

void SkipTurnCardBehavior::execute()
{

}

std::string& SkipTurnCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

bool SkipTurnCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	if (std::shared_ptr<SkipTurnCardBehavior> otherCard = std::dynamic_pointer_cast<SkipTurnCardBehavior>(otherBehavior))
	{
		return true;
	}

	return false;
}

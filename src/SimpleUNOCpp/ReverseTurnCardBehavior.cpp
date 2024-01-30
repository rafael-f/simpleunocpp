#include "ReverseTurnCardBehavior.h"
#include "KeyCodes.h"

ReverseTurnCardBehavior::ReverseTurnCardBehavior()
{
	_stringToDraw = std::string(1, KeyCodes::RIGHT_DOUBLE_ARROW) + " " + std::string(1, KeyCodes::LEFT_DOUBLE_ARROW);
}

void ReverseTurnCardBehavior::execute()
{

}

std::string& ReverseTurnCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

bool ReverseTurnCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	if (std::shared_ptr<ReverseTurnCardBehavior> otherCard = std::dynamic_pointer_cast<ReverseTurnCardBehavior>(otherBehavior))
	{
		return true;
	}

	return false;
}

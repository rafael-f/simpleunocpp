#include "SwapHandCardBehavior.h"
#include "KeyCodes.h"

SwapHandCardBehavior::SwapHandCardBehavior()
{
	_stringToDraw = std::string(1, KeyCodes::SWAP_LEFT) + " " + std::string(1, KeyCodes::SWAP_RIGHT);
}

void SwapHandCardBehavior::execute()
{
	
}

std::string& SwapHandCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

bool SwapHandCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	return true; // Can always be played (color check happens on card level).
}
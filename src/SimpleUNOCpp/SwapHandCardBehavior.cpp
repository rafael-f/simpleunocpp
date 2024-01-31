#include "SwapHandCardBehavior.h"
#include "KeyCodes.h"
#include "SwapHandCardEvent.h"

SwapHandCardBehavior::SwapHandCardBehavior()
{
	_stringToDraw = std::string(1, KeyCodes::SWAP_LEFT) + " " + std::string(1, KeyCodes::SWAP_RIGHT);
}

void SwapHandCardBehavior::execute()
{
	// player selectes another player to change hands
	Mediator::fireEvent(SwapHandCardEvent());
}

std::string& SwapHandCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

bool SwapHandCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	return true; // Can always be played.
}

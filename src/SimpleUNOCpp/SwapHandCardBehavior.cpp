#include "SwapHandCardBehavior.h"
#include "KeyCodes.h"
#include "SwapHandCardEvent.h"

const std::string SwapHandCardBehavior::NAME_TO_DRAW = "SWAP";

SwapHandCardBehavior::SwapHandCardBehavior()
{
	_symbolToDraw = std::string(1, KeyCodes::SWAP_LEFT) + " " + std::string(1, KeyCodes::SWAP_RIGHT);
}

void SwapHandCardBehavior::execute()
{
	EventBus::fireEvent(SwapHandCardEvent());
}

std::string& SwapHandCardBehavior::getSymbolToDraw()
{
	return _symbolToDraw;
}

bool SwapHandCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
	return true; // Can always be played.
}

std::string SwapHandCardBehavior::getNameToDraw()
{
	return NAME_TO_DRAW;
}

bool SwapHandCardBehavior::getGoToNextPlayer()
{
	return false;
}

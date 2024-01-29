#include "SwapHandCardBehavior.h"
#include "KeyCodes.h"

SwapHandCardBehavior::SwapHandCardBehavior()
{
	_stringToDraw = KeyCodes::SWAP_LEFT + " " + KeyCodes::SWAP_RIGHT;
}

void SwapHandCardBehavior::execute()
{
	
}

std::string& SwapHandCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

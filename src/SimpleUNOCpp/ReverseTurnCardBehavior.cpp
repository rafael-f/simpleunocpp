#include "ReverseTurnCardBehavior.h"
#include "KeyCodes.h"

ReverseTurnCardBehavior::ReverseTurnCardBehavior()
{
	_stringToDraw = KeyCodes::RIGHT_DOUBLE_ARROW + " " + KeyCodes::LEFT_DOUBLE_ARROW;
}

void ReverseTurnCardBehavior::execute()
{

}

std::string& ReverseTurnCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

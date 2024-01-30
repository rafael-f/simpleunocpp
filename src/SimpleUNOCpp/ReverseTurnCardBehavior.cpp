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

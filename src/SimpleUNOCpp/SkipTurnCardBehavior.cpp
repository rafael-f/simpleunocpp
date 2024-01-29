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

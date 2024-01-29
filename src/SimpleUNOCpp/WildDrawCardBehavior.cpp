#include "WildDrawCardBehavior.h"

WildDrawCardBehavior::WildDrawCardBehavior(const int& drawAmount) : _drawAmount(drawAmount)
{
	_stringToDraw = "+" + std::to_string(drawAmount) + " ";
}

void WildDrawCardBehavior::execute()
{

}

std::string& WildDrawCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

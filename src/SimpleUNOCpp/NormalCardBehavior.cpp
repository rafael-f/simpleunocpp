#include "NormalCardBehavior.h"

NormalCardBehavior::NormalCardBehavior(int value) : _value(value)
{
	_stringToDraw = " " + std::to_string(value) + " ";
}

void NormalCardBehavior::execute()
{

}

std::string& NormalCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

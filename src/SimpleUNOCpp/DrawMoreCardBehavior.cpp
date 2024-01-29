#include "DrawMoreCardBehavior.h"

DrawMoreCardBehavior::DrawMoreCardBehavior(const int& drawMoreAmount) : _drawMoreAmount(drawMoreAmount)
{
	_stringToDraw = "+" + std::to_string(_drawMoreAmount) + " ";
}

void DrawMoreCardBehavior::execute()
{

}

std::string& DrawMoreCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

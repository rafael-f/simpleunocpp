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

bool DrawMoreCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
    if (std::shared_ptr<DrawMoreCardBehavior> otherCard = std::dynamic_pointer_cast<DrawMoreCardBehavior>(otherBehavior))
    {
        return true;
    }

	return false;
}

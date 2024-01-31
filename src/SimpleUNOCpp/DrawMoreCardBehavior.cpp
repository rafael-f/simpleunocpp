#include "DrawMoreCardBehavior.h"
#include "DrawMoreCardEvent.h"

DrawMoreCardBehavior::DrawMoreCardBehavior(const int& drawMoreAmount) : _drawMoreAmount(drawMoreAmount)
{
	_symbolToDraw = "+" + std::to_string(_drawMoreAmount) + " ";
}

void DrawMoreCardBehavior::execute()
{
    // TODO forces next player to draw + amount cards, next player can't play
    Mediator::fireEvent(DrawMoreCardEvent(_drawMoreAmount));
}

std::string& DrawMoreCardBehavior::getSymbolToDraw()
{
	return _symbolToDraw;
}

bool DrawMoreCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
    if (std::shared_ptr<DrawMoreCardBehavior> otherCard = std::dynamic_pointer_cast<DrawMoreCardBehavior>(otherBehavior))
    {
        return true;
    }

	return false;
}

std::string DrawMoreCardBehavior::getNameToDraw()
{
    return "";
}

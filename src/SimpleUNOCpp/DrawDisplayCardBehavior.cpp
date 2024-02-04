#include "DrawDisplayCardBehavior.h"
#include "DrawDisplayCardEvent.h"

const std::string DrawDisplayCardBehavior::DRAW_NAME = "DRAW";

DrawDisplayCardBehavior::DrawDisplayCardBehavior()
{
    setAmount(1);
}

void DrawDisplayCardBehavior::execute()
{
    Mediator::fireEvent(DrawDisplayCardEvent(_amount));
    setAmount(1);
}

std::string& DrawDisplayCardBehavior::getSymbolToDraw()
{
    return _symbolToDraw;
}

bool DrawDisplayCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
    return true;
}

void DrawDisplayCardBehavior::setAmount(const int& amount)
{
    _amount = amount;
    _symbolToDraw = "+" + std::to_string(_amount) + " ";
}

std::string DrawDisplayCardBehavior::getNameToDraw()
{
    return DRAW_NAME;
}

int DrawDisplayCardBehavior::getAmount() const
{
    return _amount;
}

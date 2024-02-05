#include "DrawPileCardBehavior.h"
#include "DrawPileCardEvent.h"

const std::string DrawPileCardBehavior::DRAW_NAME = "DRAW";

DrawPileCardBehavior::DrawPileCardBehavior()
{
    setAmount(1);
}

void DrawPileCardBehavior::execute()
{
    EventBus::fireEvent(DrawPileCardEvent(_amount));
    setAmount(1);
}

std::string& DrawPileCardBehavior::getSymbolToDraw()
{
    return _symbolToDraw;
}

bool DrawPileCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
    return true;
}

void DrawPileCardBehavior::setAmount(const int& amount)
{
    _amount = amount;
    _symbolToDraw = "+" + std::to_string(_amount) + " ";
}

std::string DrawPileCardBehavior::getNameToDraw()
{
    return DRAW_NAME;
}

int DrawPileCardBehavior::getAmount() const
{
    return _amount;
}

bool DrawPileCardBehavior::getGoToNextPlayer()
{
    return true;
}
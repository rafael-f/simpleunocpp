#include "NormalCardBehavior.h"
#include "NormalCardEvent.h"

NormalCardBehavior::NormalCardBehavior(int value) : _value(value)
{
	_stringToDraw = " " + std::to_string(value) + " ";
}

void NormalCardBehavior::execute()
{
    Mediator::fireEvent(NormalCardEvent());
}

std::string& NormalCardBehavior::getStringToDraw()
{
	return _stringToDraw;
}

bool NormalCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
    if (std::shared_ptr<NormalCardBehavior> otherCard = std::dynamic_pointer_cast<NormalCardBehavior>(otherBehavior))
    {
        return _value == otherCard->getValue();
    }

    return false;
}

int NormalCardBehavior::getValue() const
{
    return _value;
}

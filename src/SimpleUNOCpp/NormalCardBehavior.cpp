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

bool NormalCardBehavior::checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior)
{
    if (std::shared_ptr<NormalCardBehavior> otherCard = std::dynamic_pointer_cast<NormalCardBehavior>(otherBehavior))
    {
        if (_value == otherCard->getValue())
        {
            return true;
        }
    }

    return false;
}

int NormalCardBehavior::getValue() const
{
    return _value;
}

#include "PlayersOption.h"
#include <iostream>
#include <string>
#include "KeyCodes.h"

PlayersOption::PlayersOption(const int& value) :
	_value(value)
{
    _length = static_cast<int>(std::to_string(value).length());
}

int PlayersOption::getValue() const
{
	return _value;
}

void PlayersOption::draw(const Window& window, const int& row, const int& column) const
{
    window.setCursorPosition(row, column);

    if (_isSelected)
    {
        std::cout << KeyCodes::TOP_LEFT_CORNER;
        for (int i = 0; i < _length; ++i)
        {
            std::cout << KeyCodes::HORIZONTAL_LINE;
        }
        std::cout << KeyCodes::TOP_RIGHT_CORNER;

        window.setCursorPosition(row + 1, column);
        std::cout << KeyCodes::VERTICAL_LINE << _value << KeyCodes::VERTICAL_LINE;
        window.setCursorPosition(row + 2, column);

        std::cout << KeyCodes::BOTTOM_LEFT_CORNER;
        for (int i = 0; i < _length; ++i)
        {
            std::cout << KeyCodes::HORIZONTAL_LINE;
        }
        std::cout << KeyCodes::BOTTOM_RIGHT_CORNER;
    }
    else
    {
        window.setCursorPosition(row + 1, column);
        std::cout << " " << _value << " ";
    }
}

void PlayersOption::setSelected(const bool& selected)
{
	_isSelected = selected;
}

int PlayersOption::getLength() const
{
    return _length;
}

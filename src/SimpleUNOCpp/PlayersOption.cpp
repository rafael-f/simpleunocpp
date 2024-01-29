#include "PlayersOption.h"
#include <Windows.h>
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

void PlayersOption::draw(const int& row, const int& column) const
{
    setCursorPosition(row, column);

    if (_isSelected)
    {
        std::cout << KeyCodes::TOP_LEFT_CORNER;
        for (int i = 0; i < _length; ++i)
        {
            std::cout << KeyCodes::HORIZONTAL_LINE;
        }
        std::cout << KeyCodes::TOP_RIGHT_CORNER;

        setCursorPosition(row + 1, column);
        std::cout << KeyCodes::VERTICAL_LINE << _value << KeyCodes::VERTICAL_LINE;
        setCursorPosition(row + 2, column);

        std::cout << KeyCodes::BOTTOM_LEFT_CORNER;
        for (int i = 0; i < _length; ++i)
        {
            std::cout << KeyCodes::HORIZONTAL_LINE;
        }
        std::cout << KeyCodes::BOTTOM_RIGHT_CORNER;
    }
    else
    {
        setCursorPosition(row + 1, column);
        std::cout << " " << _value << " ";
    }
}

void PlayersOption::setSelected(const bool& selected)
{
	_isSelected = selected;
}

void PlayersOption::setCursorPosition(const int& row, const int& column) const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD cursorPos;
    cursorPos.X = static_cast<short>(column);
    cursorPos.Y = static_cast<short>(row);

    SetConsoleCursorPosition(hConsole, cursorPos);
}

int PlayersOption::getLength() const
{
    return _length;
}

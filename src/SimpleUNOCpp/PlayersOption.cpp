#include "PlayersOption.h"
#include <windows.h>
#include <iostream>

PlayersOption::PlayersOption(const int& value) :
	_value(value)
{

}

int PlayersOption::getValue()
{
	return _value;
}

void PlayersOption::draw(const int& row, const int& column)
{
    setCursorPosition(row, column);

    char topLeft = 218;
    char horizontalLine = 196;
    char topRight = 191;
    char verticalLine = 179;
    char bottomLeft = 192;
    char bottomRight = 217;

    if (_isSelected)
    {
        std::cout << topLeft << horizontalLine << topRight;
        setCursorPosition(row + 1, column);
        std::cout << verticalLine << _value << verticalLine;
        setCursorPosition(row + 2, column);
        std::cout << bottomLeft << horizontalLine << bottomRight;
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

void PlayersOption::setCursorPosition(const int& row, const int& column)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD cursorPos;
    cursorPos.X = column;
    cursorPos.Y = row;

    SetConsoleCursorPosition(hConsole, cursorPos);
}

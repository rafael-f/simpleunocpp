#include "ColorPickItem.h"
#include <iostream>
#include "KeyCodes.h"

ColorPickItem::ColorPickItem(const Colors& color) : _color(color)
{}

int ColorPickItem::draw(Window& window, const int& row, const int& column) const
{
	const int pickerSizeColumns = 6;
	const int pickerSizeRows = 3;

	window.setCursorPosition(row, column);

	if (_isSelected)
	{
		std::cout << KeyCodes::TOP_LEFT_CORNER;
		for (int i = 0; i < pickerSizeColumns; ++i)
		{
			std::cout << KeyCodes::HORIZONTAL_LINE;
		}
		std::cout << KeyCodes::TOP_RIGHT_CORNER;
	}

	for (int r = 0; r < pickerSizeRows; ++r)
	{
		window.setCursorPosition(row + 1 + r, column);

		if (_isSelected)
		{
			window.setConsoleColor(Colors::WHITE);
			std::cout << KeyCodes::VERTICAL_LINE;
		}
		else
		{
			std::cout << " ";
		}

		window.setConsoleColor(_color);

		for (int i = 0; i < pickerSizeColumns; ++i)
		{
			std::cout << KeyCodes::FULL_BLOCK;
		}

		if (_isSelected)
		{
			window.setConsoleColor(Colors::WHITE);
			std::cout << KeyCodes::VERTICAL_LINE;
		}
	}

	window.setCursorPosition(row + 1 + pickerSizeRows, column);

	if (_isSelected)
	{
		std::cout << KeyCodes::BOTTOM_LEFT_CORNER;
		for (int i = 0; i < pickerSizeColumns; ++i)
		{
			std::cout << KeyCodes::HORIZONTAL_LINE;
		}
		std::cout << KeyCodes::BOTTOM_RIGHT_CORNER;
	}

	window.setConsoleColor(Colors::WHITE);

	return pickerSizeColumns + 2;
}

void ColorPickItem::setSelected(const bool& selected)
{
	_isSelected = selected;
}

bool ColorPickItem::getSelected() const
{
	return _isSelected;
}

Colors ColorPickItem::getSelectedColor() const
{
	return _color;
}

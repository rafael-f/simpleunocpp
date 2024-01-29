#include "Card.h"
#include "KeyCodes.h"
#include <iostream>

Card::Card(const Colors& color, std::shared_ptr<CardBehavior> behavior) :
	_color(color), _behavior(behavior)
{
	_drawLength = 5; // TODO
}

void Card::setCanBePlayed(const Card& cardOnGame)
{
	_canBePlayed = true; // TODO
}

// TODO how to improve this salad? probably easier to make a template in a txt file?
void Card::draw(const int& row, const int& column, const Window& window)
{
	window.setCursorPosition(row, column);
	
	Colors borderColor;

	if (!_canBePlayed)
	{
		borderColor = Colors::GREEN;
	}
	else
	{
		borderColor = Colors::RED;
	}

	// Draw selection border
	if (_isSelected)
	{
		window.setConsoleColor(borderColor);

		std::cout << KeyCodes::TOP_LEFT_CORNER;
		for (int i = 0; i < CARD_LENGTH; ++i)
		{
			std::cout << KeyCodes::HORIZONTAL_LINE;
		}
		std::cout << KeyCodes::TOP_RIGHT_CORNER;
	}

	// Go to next line
	window.setCursorPosition(row + 1, column);

	// Draw selection border
	if (_isSelected)
	{
		std::cout << KeyCodes::VERTICAL_LINE;
	}
	else
	{
		std::cout << " ";
	}

	// Set card color and draw top card border
	window.setConsoleColor(_color);

	std::cout << KeyCodes::TOP_LEFT_CORNER_DOUBLE;
	for (int i = 0; i < CARD_LENGTH - 2; ++i)
	{
		std::cout << KeyCodes::HORIZONTAL_LINE_DOUBLE;
	}
	std::cout << KeyCodes::TOP_RIGHT_CORNER_DOUBLE;

	// Draw right selection border
	if (_isSelected)
	{
		window.setConsoleColor(borderColor);
		std::cout << KeyCodes::VERTICAL_LINE;
	}
	
	// Go To next row
	window.setCursorPosition(row + 2, column);

	// Draw selection border
	if (_isSelected)
	{
		std::cout << KeyCodes::VERTICAL_LINE;
		window.setConsoleColor(_color);
	}
	else
	{
		std::cout << " ";
	}

	// Draw both card borders and card text
	std::cout << KeyCodes::VERTICAL_LINE_DOUBLE << _behavior->getStringToDraw();
	for (int i = 0; i < CARD_LENGTH - 5; ++i) // TODO 5 is 2 from borders and 3 from card string
	{
		std::cout << " ";
	}
	std::cout << KeyCodes::VERTICAL_LINE_DOUBLE;

	// Draw right selection border
	if (_isSelected)
	{
		window.setConsoleColor(borderColor);
		std::cout << KeyCodes::VERTICAL_LINE;
	}

	// Go to next line
	window.setCursorPosition(row + 3, column);

	// draw selection border
	if (_isSelected)
	{
		std::cout << KeyCodes::VERTICAL_LINE;
		window.setConsoleColor(_color);
	}
	else
	{
		std::cout << " ";
	}

	// draw card border
	std::cout << KeyCodes::VERTICAL_LINE_DOUBLE;

	// draw middle empty line
	for (int i = 0; i < CARD_LENGTH - 2; ++i)
	{
		std::cout << " ";
	}

	// draw card border
	std::cout << KeyCodes::VERTICAL_LINE_DOUBLE;

	// Draw right selection border
	if (_isSelected)
	{
		window.setConsoleColor(borderColor);
		std::cout << KeyCodes::VERTICAL_LINE;
	}

	// Go to next line
	window.setCursorPosition(row + 4, column);

	if (_isSelected)
	{
		std::cout << KeyCodes::VERTICAL_LINE;
		window.setConsoleColor(_color);
	}
	else
	{
		std::cout << " ";
	}

	std::cout << KeyCodes::VERTICAL_LINE_DOUBLE;
	for (int i = 0; i < CARD_LENGTH - 5; ++i)
	{
		std::cout << " ";
	}
	std::cout << _behavior->getStringToDraw() << KeyCodes::VERTICAL_LINE_DOUBLE;
	if (_isSelected)
	{
		window.setConsoleColor(borderColor);
		std::cout << KeyCodes::VERTICAL_LINE;
	}

	// Go to next line
	window.setCursorPosition(row + 5, column);
	if (_isSelected)
	{
		std::cout << KeyCodes::VERTICAL_LINE;
		window.setConsoleColor(_color);
	}
	else
	{
		std::cout << " ";
	}
	
	std::cout << KeyCodes::BOTTOM_LEFT_CORNER_DOUBLE;
	for (int i = 0; i < CARD_LENGTH - 2; ++i)
	{
		std::cout << KeyCodes::HORIZONTAL_LINE_DOUBLE;
	}
	std::cout << KeyCodes::BOTTOM_RIGHT_CORNER_DOUBLE;
	if (_isSelected)
	{
		window.setConsoleColor(borderColor);
		std::cout << KeyCodes::VERTICAL_LINE;
	}

	// Go to next line
	window.setCursorPosition(row + 6, column);
	if (_isSelected)
	{
		std::cout << KeyCodes::BOTTOM_LEFT_CORNER;
		for (int i = 0; i < CARD_LENGTH; ++i)
		{
			std::cout << KeyCodes::HORIZONTAL_LINE;
		}
		std::cout << KeyCodes::BOTTOM_RIGHT_CORNER;
	}

	window.setConsoleColor(Colors::WHITE);
}

void Card::setSelected(bool selected)
{
	_isSelected = selected;
}

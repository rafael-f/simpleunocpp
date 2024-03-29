#include "Card.h"
#include "KeyCodes.h"
#include <iostream>
#include "WildDrawCardBehavior.h"
#include "SwapHandCardBehavior.h"

Card::Card(const Colors& color, std::shared_ptr<CardBehavior> behavior) :
	_behavior(behavior), _color(color)
{
}

void Card::setCanBePlayed(const bool& canBePlayed)
{
	_canBePlayed = canBePlayed;
}

bool Card::getCanBePlayed() const
{
	return _canBePlayed;
}

// TODO improve this? probably easier to make a template in a txt file?
void Card::draw(const int& row, const int& column, const Window& window)
{
	window.setCursorPosition(row, column);
	
	Colors borderColor = Colors::WHITE;
	
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

	std::string x = _behavior->getSymbolToDraw();

	// Draw both card borders and card text
	std::cout << KeyCodes::VERTICAL_LINE_DOUBLE << _behavior->getSymbolToDraw();
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
	std::string cardName = Window::fillWithSpaces(_behavior->getNameToDraw(), CARD_LENGTH - 2);
	std::cout << cardName;

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
	std::cout << _behavior->getSymbolToDraw() << KeyCodes::VERTICAL_LINE_DOUBLE;
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

bool Card::getSelected() const
{
	return _isSelected;
}

Colors Card::getColor() const
{
	return _color;
}

std::shared_ptr<CardBehavior> Card::getBehavior()
{
	return _behavior;
}

bool Card::checkCanBePlayed(const std::shared_ptr<Card> otherCard)
{
	return _behavior->checkCanBePlayed(otherCard->getBehavior());
}

bool Card::getAcceptOnlySameType() const
{
	return _acceptOnlySameType;
}

void Card::setAcceptOnlySameType(const bool& set)
{
	_acceptOnlySameType = set;
}

bool Card::goToNextPlayer() const
{
	return _behavior->getGoToNextPlayer();
}

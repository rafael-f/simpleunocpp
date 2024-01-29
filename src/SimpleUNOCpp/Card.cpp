#include "Card.h"

Card::Card(const Colors& color, std::shared_ptr<CardBehavior> behavior) :
	_color(color), _behavior(behavior)
{
	_drawLength = 5; // TODO
}

void Card::setCanBePlayed(const Card& cardOnGame)
{
	_canBePlayed = true; // TODO
}

void Card::draw(const int& row, const int& column, const Window& window)
{
	window.setCursorPosition(row, column);
	window.setConsoleColor(_color);
	//TODO
	// if selected draw border

	window.setConsoleColor(Colors::WHITE);
}

void Card::setSelected(bool selected)
{
	_isSelected = selected;
}

int Card::getDrawLength()
{
	return _drawLength;
}

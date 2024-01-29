#pragma once
#include <memory>
#include <string>
#include "CardBehavior.h"
#include "Colors.h"
#include "Window.h"

// A card contains many card behaviors that can all alter something in gameplay.
class Card
{
public:
	Card(const Colors& color, std::shared_ptr<CardBehavior> behavior);

	void setCanBePlayed(const Card& cardOnGame);

	void draw(const int& row, const int& column, const Window& window);

	void setSelected(bool selected);

private:
	std::shared_ptr<CardBehavior> _behavior;

	Colors _color;

	bool _isSelected = false;

	bool _canBePlayed;

	int _drawLength;

	std::string symbol;

	static const int CARD_LENGTH = 8;
};

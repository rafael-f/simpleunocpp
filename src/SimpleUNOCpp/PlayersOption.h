#pragma once
#include "Window.h"

// Used to get desired number of players that will play the game
class PlayersOption
{
public:
	explicit PlayersOption(const int& value);

	int getValue() const;

	void draw(const Window& window, const int& row, const int& column) const;

	void setSelected(const bool& selected);

	int getLength() const;

private:
	int _value;

	bool _isSelected = false;

	int _length;
};

#pragma once

// Used to get desired number of players that will play the game
class PlayersOption
{
public:
	explicit PlayersOption(const int& value);

	int getValue();

	void draw(const int& row, const int& column);

	//void drawOnScreen(const short& row, const short& column, const std::vector<std::string> values);

	void setSelected(const bool& selected);

private:
	int _value;

	bool _isSelected = false;

	int _length;

	void setCursorPosition(const int& row, const int& column);
};

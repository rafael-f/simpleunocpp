#pragma once
#include "State.h"
#include <string>
#include <vector>
#include "PlayersOption.h"
#include <memory>

// State to get number of participating players.
class PlayerSelectState : public State
{
public:
	PlayerSelectState();

	void draw() override;

	void handleInput() override;

private:
	static const std::string AMOUNT_OF_PLAYERS_QUESTION;

	static const int MIN_AMOUNT = 2;
	static const int MAX_AMOUNT = 10;

	std::vector<std::unique_ptr<PlayersOption>> _options;

	int _selectedIndex = 0;

	void selectPreviousOption();

	void selectNextOption();
};

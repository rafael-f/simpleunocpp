#pragma once
#include "State.h"
#include <vector>
#include <string>

// Main Menu, draws game logo and moves to next state.
class MenuState : public State
{
public:
	MenuState();

	void draw() override;

	void handleInput(const std::string& input) override;

private:
	std::vector<std::string> _titleLines;

	void loadTitleLines();

	static const std::string TITLE_FILE_PATH;
};

#pragma once
#include "State.h"
#include <vector>
#include <string>

class MenuState : public State
{
public:
	MenuState();

	void draw() override;

	void handleInput(const std::string& input) override;

private:
	std::vector<std::string> _titleLines;
};

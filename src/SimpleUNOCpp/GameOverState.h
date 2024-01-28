#pragma once
#include "State.h"

class GameOverState : public State
{
public:
	void draw() override;

	void handleInput(const std::string& input) override;
};

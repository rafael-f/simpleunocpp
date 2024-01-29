#pragma once
#include "State.h"

// State used to retrieve player names.
class PlayerNamesState : public State
{
	void draw(const Window& window) override;

	void handleInput() override;
};

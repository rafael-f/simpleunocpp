#pragma once
#include "State.h"

// State used to retrieve player names.
class PlayerNamesState : public State
{
	void draw() override;

	void handleInput() override;
};

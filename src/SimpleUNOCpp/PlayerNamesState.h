#pragma once
#include "State.h"

class PlayerNamesState : public State
{
	void draw() override;

	void handleInput() override;
};

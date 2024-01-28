#pragma once
#include "State.h"
#include <memory>
#include "TurnManager.h"

// State the game is when in playing mode.
class GameState : public State
{
public:
	void draw() override;

	void handleInput() override;

private:
	std::unique_ptr<TurnManager> _turnManager;
};

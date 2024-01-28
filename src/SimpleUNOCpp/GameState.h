#pragma once
#include "State.h"
#include <memory>
#include "TurnManager.h"

class GameState : public State
{
public:
	void draw() override;

	void handleInput(const std::string& input) override;

private:
	std::unique_ptr<TurnManager> _turnManager;
};

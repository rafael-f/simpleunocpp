#pragma once
#include "State.h"
#include <memory>
#include "TurnManager.h"

class GameState : public State
{
public:
	void draw(Window& window) override;

private:
	std::unique_ptr<TurnManager> _turnManager;
};

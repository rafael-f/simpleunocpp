#pragma once
#include "State.h"
#include <memory>
#include "TurnManager.h"

class GameState : public State
{
private:
	std::unique_ptr<TurnManager> _turnManager;
};

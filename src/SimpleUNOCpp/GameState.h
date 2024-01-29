#pragma once
#include "State.h"
#include <memory>
#include "TurnManager.h"
#include "PlayerManager.h"

// State the game is when in playing mode.
class GameState : public State
{
public:
	void draw(Window& window) override;

	void handleInput() override;

	void setData(std::shared_ptr<TransitionData> transitionData) override;

private:
	std::unique_ptr<TurnManager> _turnManager;

	std::shared_ptr<PlayerManager> _playerManager;
};

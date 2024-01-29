#pragma once
#include "State.h"
#include <vector>
#include "PlayerManager.h"

// State used to ask for player names.
class PlayerNamesState : public State
{
public:
	void draw(Window& window) override;

	void handleInput() override;

	void setData(std::shared_ptr<TransitionData> transitionData) override;

private:
	int _numberOfPlayers;

	int _currentPlayerEditingIndex;

	std::shared_ptr<PlayerManager> _playerManager;

	std::string _currentEditingName;

	void transitionToGame();

	void handleEnterKey();
};

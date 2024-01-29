#pragma once
#include "State.h"

// State to display which player has won the game and ask if the players will start a new game or quit.
class GameOverState : public State
{
public:
	void draw(Window& window) override;

	void handleInput() override;

	void setData(std::shared_ptr<TransitionData> transitionData) override;
};

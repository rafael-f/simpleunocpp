#pragma once
#include "State.h"
#include <string>

// State to display which player has won the game and ask if the players will start a new game or quit.
class GameOverState : public State
{
public:
	void draw(Window& window) override;

	void handleInput() override;

	void setData(std::shared_ptr<TransitionData> transitionData) override;

private:
	std::string _winnerName;
};

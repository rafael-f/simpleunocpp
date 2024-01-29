#pragma once
#include "State.h"

// State used to retrieve player names.
class PlayerNamesState : public State
{
public:
	void draw(const Window& window) override;

	void handleInput() override;

	void setData(std::shared_ptr<TransitionData> transitionData) override;

private:
	int _numberOfPlayers;
};

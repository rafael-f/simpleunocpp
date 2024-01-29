#pragma once
#include "State.h"
#include <memory>
#include "PlayerManager.h"
#include "Card.h"

// State the game is when in playing mode.
class GameState : public State
{
public:
	void draw(Window& window) override;

	void handleInput() override;

	void setData(std::shared_ptr<TransitionData> transitionData) override;

private:

	std::shared_ptr<PlayerManager> _playerManager;

	std::vector<std::shared_ptr<Card>> _drawPile;

	std::vector<std::shared_ptr<Card>> _discardPile;

	void createCardsOnDrawPile();

	void shuffleVector(std::vector<std::shared_ptr<Card>>& vector) const;
};

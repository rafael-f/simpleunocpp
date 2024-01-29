#pragma once
#include <memory>
#include "Card.h"
#include "PlayerManager.h"
#include "State.h"

// State the game is when in playing mode.
class GameState : public State
{
public:
	void draw(Window& window) override;

	void handleInput() override;

	void setData(std::shared_ptr<TransitionData> transitionData) override;

private:
	static const int NUMBER_OF_START_CARDS_PER_PLAYER = 7;

	std::shared_ptr<PlayerManager> _playerManager;

	std::vector<std::shared_ptr<Card>> _drawPile;

	std::vector<std::shared_ptr<Card>> _discardPile;

	void startGame();

	void initializePlayersHands();

	void discardFirstCard();

	void addCardToDiscardPile(std::shared_ptr<Card> card);

	void drawDiscardedPile(Window& window, const int& nextRow);

	int _currentPlayerIndex;

	void clearPiles();

	int _turnDirection = 1;

	void drawArrow(Window& window, const char& arrow, const int& row, int& column);
};

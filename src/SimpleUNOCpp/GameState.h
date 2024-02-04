#pragma once
#include <memory>
#include "Card.h"
#include "PlayerManager.h"
#include "State.h"
#include "GameStates.h"
#include "DrawDisplayCardEvent.h"
#include "DrawDiscardedCardEvent.h"
#include "DrawMoreCardEvent.h"
#include "WildDrawCardEvent.h"
#include "ColorPickItem.h"

// State the game is when in playing mode.
class GameState : public State
{
public:
	GameState();

	void draw(Window& window) override;

	void handleInput() override;

	void setData(std::shared_ptr<TransitionData> transitionData) override;

private:
	static const int NUMBER_OF_START_CARDS_PER_PLAYER = 2;

	static const int NUMBER_OF_CARDS_TO_PUNISH = 2;

	std::shared_ptr<PlayerManager> _playerManager;

	std::vector<std::shared_ptr<Card>> _drawPile;

	std::vector<std::shared_ptr<Card>> _discardPile;

	void startGame();

	void initializePlayersHands();

	void discardFirstCard();

	void addCardToDiscardPile(std::shared_ptr<Card> card);

	void drawDiscardedPile(Window& window, int& nextRow);

	void drawDrawPile(Window& window, int& nextRow);

	void clearPiles();

	int _turnDirection = 1;

	GameStates _currentState = GameStates::NORMAL;

	// TODO separate all methods below in their own states
	void drawNormalState(Window& window);
	void handleInputNormalState();

	void drawDisplayNewCardsState(Window& window);
	void handleInputDisplayNewCardsState();

	void drawForcedDrawDiscardedState(Window& window);
	void handleInputForcedDrawDiscardedState();

	void drawForcedSkipState(Window& window);
	void handleInputForcedSkipState();

	void drawSelectPlayerState(Window& window);
	void handleInputSelectPlayerState();

	void drawSelectColorState(Window& window);
	void handleInputSelectColorState();

	void drawForcedDrawWildState(Window& window);
	void handleInputForcedDrawWildState();

	void drawForcedDrawPunishState(Window& window);
	void handleInputForcedDrawPunishState();

	std::unique_ptr<Card> _drawCard;

	std::string _currentMessage;

	void handleReverseTurnEvent();

	void handleDrawCardEvent(const DrawDisplayCardEvent& eventData);

	bool endTurn = false;

	void handleDrawDiscardedCardEvent(const DrawDiscardedCardEvent& eventData);

	void handleDrawMoreCardEvent(const DrawMoreCardEvent& eventData);

	int _swapHandSelectedIndex = 0;

	void handleSwapHandCardEvent();

	std::vector<std::shared_ptr<Player>> _availableSwapHandPlayers;

	void handleWildDrawCardEvent(const WildDrawCardEvent& eventData);

	std::vector<std::shared_ptr<ColorPickItem>> _colorsToPick;

	int _selectedColorIndex = 0;

	Colors _forcedColor = Colors::WHITE;
};

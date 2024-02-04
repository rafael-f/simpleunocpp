#pragma once
#include <memory>
#include "Card.h"
#include "PlayerManager.h"
#include "State.h"
#include "GameStates.h"
#include "DrawPileCardEvent.h"
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
	static const int NUMBER_OF_START_CARDS_PER_PLAYER = 7;

	static const int NUMBER_OF_CARDS_TO_PUNISH = 2;

	std::shared_ptr<PlayerManager> _playerManager;

	std::vector<std::shared_ptr<Card>> _drawPile;

	std::vector<std::shared_ptr<Card>> _discardPile;

	void startGame();

	void initializePlayersHands();

	void discardFirstCard();

	void addCardToDiscardPile(std::shared_ptr<Card> card);

	void drawDiscardedPile(const Window& window, const int& nextRow);

	void drawDrawPile(const Window& window, const int& nextRow);

	void clearPiles();

	int _turnDirection = 1;

	GameStates _currentState = GameStates::NORMAL;

	// TODO separate all methods below in their own states
	void drawNormalState(Window& window);
	void handleInputNormalState();

	void handleEndTurnInput(const int& input);
	void handleNormalTurnInput(const int& input);
	void handleSayUNOInput() const;
	void handleArrowInput();
	void handleDrawCardInput();
	void tryToUseSelectedCard();
	void useLastPlayerCard(std::shared_ptr<Card> selectedCard);
	void useSelectedCard(std::shared_ptr<Card> selectedCard);

	void handleInputForcedDrawDiscardedState();

	void handleInputForcedSkipState();

	void drawSelectPlayerState(const Window& window) const;
	void handleInputSelectPlayerState();

	void drawSelectColorState(const Window& window) const;
	void handleInputSelectColorState();

	void handleInputForcedDrawWildState();

	void handleInputForcedDrawPunishState();

	std::unique_ptr<Card> _drawCard;

	std::string _currentMessage;

	void handleReverseTurnEvent();

	void handleDrawCardEvent(const DrawPileCardEvent& eventData);

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

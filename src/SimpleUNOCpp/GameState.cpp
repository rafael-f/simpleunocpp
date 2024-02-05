#include <iostream>
#include "GameState.h"
#include "CardsLoader.h"
#include "EventBus.h"
#include "PlayerManagerTransitionData.h"
#include "DrawPileCardBehavior.h"
#include "ReverseTurnCardEvent.h"
#include "SkipTurnCardEvent.h"
#include "SwapHandCardEvent.h"

GameState::GameState()
{
	// TODO move these somewhere else?
	EventBus::registerListener<ReverseTurnCardEvent>([this](const ReverseTurnCardEvent&)
		{
			handleReverseTurnEvent();
		});

	EventBus::registerListener<DrawPileCardEvent>([this](const DrawPileCardEvent& eventData)
		{
			handleDrawCardEvent(eventData);
		});

	EventBus::registerListener<DrawDiscardedCardEvent>([this](const DrawDiscardedCardEvent& eventData)
		{
			handleDrawDiscardedCardEvent(eventData);
		});

	EventBus::registerListener<DrawMoreCardEvent>([this](const DrawMoreCardEvent& eventData)
		{
			handleDrawMoreCardEvent(eventData);
		});

	EventBus::registerListener<SkipTurnCardEvent>([this](const SkipTurnCardEvent&)
		{
			_currentState = GameStates::FORCED_SKIP;
		});

	EventBus::registerListener<SwapHandCardEvent>([this](const SwapHandCardEvent&)
		{
			handleSwapHandCardEvent();
		});

	EventBus::registerListener<WildDrawCardEvent>([this](const WildDrawCardEvent& eventData)
		{
			handleWildDrawCardEvent(eventData);
		});

	for (int c = static_cast<int>(Colors::RED); c < static_cast<int>(Colors::WHITE); ++c)
	{
		Colors color = static_cast<Colors>(c);
		_colorsToPick.emplace_back(std::make_shared<ColorPickItem>(color));
	}
}

void GameState::draw(Window& window)
{
	switch (_currentState)
	{
	case GameStates::FORCED_DRAW_DISCARD:

		_currentMessage = " PRESS ENTER TO DRAW 2 CARDS FROM DISCARD PILE"; // TODO replace 2 with amount
		_playerManager->getSelectedPlayer()->setSelectedCard(-1);
		_drawCard->setSelected(true);
		break;
	case GameStates::FORCED_SKIP:
		_currentMessage = " PRESS ENTER TO SKIP TURN";
		_playerManager->getSelectedPlayer()->setSelectedCard(-1);
		_drawCard->setSelected(false);
		break;
	case GameStates::SELECT_PLAYER:
		drawSelectPlayerState(window);
		return;
	case GameStates::SELECT_COLOR:
		drawSelectColorState(window);
		return;
	case GameStates::FORCED_DRAW_WILD:
		_currentMessage = " PRESS ENTER TO DRAW 4 CARDS"; // TODO replace 4 with amount
		_playerManager->getSelectedPlayer()->setSelectedCard(-1);
		_drawCard->setSelected(true);
		break;
	case GameStates::FORCED_DRAW_PUNISH:
		_currentMessage = " YOU DIDN'T SAY UNO, DRAW 2 CARDS";
		_playerManager->getSelectedPlayer()->setSelectedCard(-1);
		_drawCard->setSelected(true);
		break;
	default:
		break;
	}
	
	drawNormalState(window);
}

void GameState::handleInput()
{
	switch (_currentState)
	{
	case GameStates::NORMAL:
	case GameStates::FORCED_DRAW:
		handleInputNormalState();
		break;
	case GameStates::DISPLAY_NEW_CARDS:
		break;
	case GameStates::FORCED_DRAW_DISCARD:
		handleInputForcedDrawDiscardedState();
		break;
	case GameStates::FORCED_SKIP:
		handleInputForcedSkipState();
		break;
	case GameStates::SELECT_PLAYER:
		handleInputSelectPlayerState();
		break;
	case GameStates::SELECT_COLOR:
		handleInputSelectColorState();
		break;
	case GameStates::FORCED_DRAW_WILD:
		handleInputForcedDrawWildState();
		break;
	case GameStates::FORCED_DRAW_PUNISH:
		handleInputForcedDrawPunishState();
		break;
	}
}

void GameState::setData(std::shared_ptr<TransitionData> transitionData)
{
	std::shared_ptr<PlayerManagerTransitionData> data = std::dynamic_pointer_cast<PlayerManagerTransitionData>(transitionData);
	_playerManager = data->playerManager;

	_drawCard = std::make_unique<Card>(Colors::WHITE, std::make_shared<DrawPileCardBehavior>());
	_drawCard->setCanBePlayed(true);

	startGame();
}

void GameState::startGame()
{
	_playerManager->shufflePlayers();

	clearPiles();

	CardsLoader::createCards(_drawPile);

	initializePlayersHands();

	discardFirstCard();

	_playerManager->updatePlayerState(0, _discardPile.back());

	_currentState = GameStates::NORMAL;

	_currentMessage = "";
}

void GameState::clearPiles()
{
	if (!_drawPile.empty())
	{
		_drawPile.clear();
	}

	if (!_discardPile.empty())
	{
		_discardPile.clear();
	}
}

void GameState::initializePlayersHands()
{
	for (std::shared_ptr<Player> player : _playerManager->getPlayers())
	{
		for (int i = 0; i < NUMBER_OF_START_CARDS_PER_PLAYER; ++i)
		{
			player->addCard(_drawPile.back());
			_drawPile.pop_back();
		}
	}
}

void GameState::discardFirstCard()
{
	addCardToDiscardPile(_drawPile.back());
	_drawPile.pop_back();
}

void GameState::addCardToDiscardPile(const std::shared_ptr<Card>& card)
{
	_discardPile.push_back(card); // todo ?
}

void GameState::drawDiscardedPile(const Window& window, const int& nextRow)
{
	window.setCursorPosition(nextRow + 3, 0);
	std::string cardsDiscarded = "CARDS DISCARDED : " + std::to_string(_discardPile.size());
	std::cout << cardsDiscarded;

	_discardPile.back()->draw(nextRow, static_cast<int>(cardsDiscarded.length()) + 1, window);
}

void GameState::drawDrawPile(const Window& window, const int& nextRow)
{
	window.setCursorPosition(nextRow + 3, 35);
	std::string drawCounter = "CARDS ON DRAW PILE : " + std::to_string(_drawPile.size());
	std::cout << drawCounter;

	_drawCard->draw(nextRow, static_cast<int>(drawCounter.length()) + 36, window);
}

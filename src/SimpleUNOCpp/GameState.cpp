#include <conio.h>
#include <iostream>
#include "GameState.h"
#include "CardsLoader.h"
#include "KeyCodes.h"
#include "Mediator.h"
#include "PlayerManagerTransitionData.h"
#include "QuitGameEvent.h"
#include "DrawDisplayCardBehavior.h"

void GameState::draw(Window& window)
{
	switch (_currentState)
	{
	case GameStates::NORMAL:
		drawNormalState(window);
		break;
	case GameStates::DISPLAY_NEW_CARDS:
		break;
	case GameStates::FORCED_DRAW:
		break;
	case GameStates::FORCED_SKIP:
		break;
	case GameStates::SELECT_PLAYER:
		break;
	case GameStates::SELECT_COLOR:
		break;
	}
}

void GameState::handleInput()
{
	switch (_currentState)
	{
	case GameStates::NORMAL:
		handleInputNormalState();
		break;
	case GameStates::DISPLAY_NEW_CARDS:
		break;
	case GameStates::FORCED_DRAW:
		break;
	case GameStates::FORCED_SKIP:
		break;
	case GameStates::SELECT_PLAYER:
		break;
	case GameStates::SELECT_COLOR:
		break;
	}
}

void GameState::setData(std::shared_ptr<TransitionData> transitionData)
{
	std::shared_ptr<PlayerManagerTransitionData> data = std::dynamic_pointer_cast<PlayerManagerTransitionData>(transitionData);
	_playerManager = data->playerManager;

	_drawCard = std::make_unique<Card>(Colors::WHITE, std::make_shared<DrawDisplayCardBehavior>());

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

// TODO, is it better to make cards unique_ptrs instead and move them between the vectors?
void GameState::addCardToDiscardPile(std::shared_ptr<Card> card)
{
	_discardPile.push_back(card);
}

void GameState::drawDiscardedPile(Window& window, int& nextRow)
{
	window.setCursorPosition(nextRow + 3, 0);
	std::string cardsDiscarded = "CARDS DISCARDED : " + std::to_string(_discardPile.size());
	std::cout << cardsDiscarded;

	_discardPile.back()->draw(nextRow, static_cast<int>(cardsDiscarded.length()) + 1, window);
}

void GameState::drawDrawPile(Window& window, int& nextRow)
{
	window.setCursorPosition(nextRow + 3, 35);
	std::string drawCounter = "CARDS ON DRAW PILE : " + std::to_string(_drawPile.size());
	std::cout << drawCounter;

	_drawCard->draw(nextRow, static_cast<int>(drawCounter.length()) + 36, window);
}

void GameState::drawNormalState(Window& window)
{
	int nextRow = _playerManager->drawPlayersHeader(window, _turnDirection);

	drawDiscardedPile(window, nextRow);

	drawDrawPile(window, nextRow);

	nextRow += 6;

	_playerManager->drawPlayerCards(window, nextRow);
}

void GameState::handleInputNormalState()
{
	int input = _getch();
	if (input == KeyCodes::ESCAPE_KEY)
	{
		Mediator::fireEvent(QuitGameEvent());
	}
	else if (input == KeyCodes::ARROW_1 || input == KeyCodes::ARROW_2)
	{
		input = _getch();

		switch (input)
		{
		case KeyCodes::LEFT_ARROW:
			_playerManager->getSelectedPlayer()->selectCard(-1);
			break;
		case KeyCodes::RIGHT_ARROW:
			_playerManager->getSelectedPlayer()->selectCard(1);
			break;
		case KeyCodes::UP_ARROW:
			// TODO select draw pile
			break;
		case KeyCodes::DOWN_ARROW:
			// TODO select player hand
			break;
		}
	}
}

void GameState::drawDisplayNewCardsState(Window& window)
{

}

void GameState::handleInputDisplayNewCardsState()
{

}

void GameState::drawForcedDrawState(Window& window)
{

}

void GameState::handleInputForcedDrawState()
{

}

void GameState::drawForcedSkipState(Window& window)
{

}

void GameState::handleInputForcedSkipState()
{

}

void GameState::drawSelectPlayerState(Window& window)
{

}

void GameState::handleInputSelectPlayerState()
{

}

void GameState::drawSelectColorState(Window& window)
{

}

void GameState::handleInputSelectColorState()
{

}

#include <conio.h>
#include <iostream>
#include "GameState.h"
#include "CardsLoader.h"
#include "KeyCodes.h"
#include "Mediator.h"
#include "PlayerManagerTransitionData.h"
#include "QuitGameEvent.h"

void GameState::draw(Window& window)
{
	window.showPrompt(false);

	int nextRow = _playerManager->drawPlayersHeader(window, _turnDirection);

	drawDiscardedPile(window, nextRow);
}

void GameState::handleInput()
{
	int input = _getch();
	if (input == KeyCodes::ESCAPE_KEY)
	{
		QuitGameEvent quitGameEvent;
		Mediator::fireEvent(quitGameEvent);
	}
}

void GameState::setData(std::shared_ptr<TransitionData> transitionData)
{
	std::shared_ptr<PlayerManagerTransitionData> data = std::dynamic_pointer_cast<PlayerManagerTransitionData>(transitionData);
	_playerManager = data->playerManager;

	startGame();
}

void GameState::startGame()
{
	_playerManager->shufflePlayers();

	_playerManager->selectPlayer(0);

	clearPiles();

	CardsLoader::createCards(_drawPile);

	initializePlayersHands();

	discardFirstCard();
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

void GameState::drawDiscardedPile(Window& window, const int& nextRow)
{
	window.setCursorPosition(nextRow + 2, 0);

	std::string cardsDiscarded = "CARDS DISCARDED : " + std::to_string(_discardPile.size());
	std::cout << cardsDiscarded;

	_discardPile.back()->draw(nextRow, static_cast<int>(cardsDiscarded.length()) + 1, window);

}

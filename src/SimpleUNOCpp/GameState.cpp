#include <conio.h>
#include <iostream>
#include "GameState.h"
#include "CardsLoader.h"
#include "KeyCodes.h"
#include "Mediator.h"
#include "PlayerManagerTransitionData.h"
#include "QuitGameEvent.h"
#include "DrawDisplayCardBehavior.h"
#include "VectorHelper.h"
#include "ReverseTurnCardEvent.h"

GameState::GameState()
{
	Mediator::registerListener<ReverseTurnCardEvent>([this](const ReverseTurnCardEvent&)
		{
			handleReverseTurnEvent();
		});

	Mediator::registerListener<DrawDisplayCardEvent>([this](const DrawDisplayCardEvent& eventData)
		{
			handleDrawCardEvent(eventData);
		});

	Mediator::registerListener<DrawDiscardedCardEvent>([this](const DrawDiscardedCardEvent& eventData)
		{
			handleDrawDiscardedCardEvent(eventData);
		});
}

void GameState::draw(Window& window)
{
	switch (_currentState)
	{
	case GameStates::NORMAL:
		break;
	case GameStates::DISPLAY_NEW_CARDS:
		break;
	case GameStates::FORCED_DRAW_DISCARD:
		_currentMessage = "PRESS ENTER TO DRAW 2 CARDS FROM DISCARD PILE";
		_playerManager->getSelectedPlayer()->setSelectedCard(-1);
		_drawCard->setSelected(true);
		//drawForcedDrawDiscardedState(window);
		break;
	case GameStates::FORCED_SKIP:
		break;
	case GameStates::SELECT_PLAYER:
		break;
	case GameStates::SELECT_COLOR:
		break;
	}
	
	drawNormalState(window);
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
	case GameStates::FORCED_DRAW_DISCARD:
		handleInputForcedDrawDiscardedState();
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

#include "DrawDiscardedCardBehavior.h"

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

	// TODO remove
	for (int i = 0; i < _drawPile.size(); ++i)
	{
		if (std::shared_ptr<DrawDiscardedCardBehavior> behavior = std::dynamic_pointer_cast<DrawDiscardedCardBehavior>(_drawPile[i]->getBehavior()))
		{
			_playerManager->getPlayers()[0]->addCard(_drawPile[i]);
			_drawPile.erase(_drawPile.begin() + i);
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
	_discardPile.push_back(card); // TODO ?????
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

	++nextRow;
	window.setCursorPosition(nextRow, 0);

	std::cout << "CURRENT PLAYER : " << _playerManager->getSelectedPlayer()->getName();

	if (endTurn)
	{
		window.setConsoleColor(Colors::GREEN);
		std::cout << " PRESS ENTER TO END TURN";
		window.setConsoleColor(Colors::WHITE);
	}
	else if (_currentMessage.length() > 0)
	{
		window.setConsoleColor(Colors::RED);
		std::cout << _currentMessage;
		window.setConsoleColor(Colors::WHITE);
		_currentMessage = "";
	}
	else
	{
		std::cout << " USE A CARD OR DRAW ANOTHER CARD.";
	}

	++nextRow;

	drawDiscardedPile(window, nextRow);

	drawDrawPile(window, nextRow);

	nextRow += 6;

	_playerManager->drawPlayerCards(window, nextRow);
}

// TODO improve this
void GameState::handleInputNormalState()
{
	int input = _getch();

	if(endTurn)
	{
		if (input == KeyCodes::ENTER_KEY)
		{
			_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
			_drawCard->setSelected(false);
			endTurn = false;
		}
	}
	else
	{
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
				if (!_drawCard->getSelected())
				{
					_playerManager->getSelectedPlayer()->selectCard(-1);
				}
				break;
			case KeyCodes::RIGHT_ARROW:
				if (!_drawCard->getSelected())
				{
					_playerManager->getSelectedPlayer()->selectCard(1);
				}
				break;
			case KeyCodes::UP_ARROW:
				if (!_drawCard->getSelected())
				{
					_playerManager->getSelectedPlayer()->setSelectedCard(-1);
					_drawCard->setSelected(true);
				}
				break;
			case KeyCodes::DOWN_ARROW:
				if (_drawCard->getSelected())
				{
					_playerManager->getSelectedPlayer()->setSelectedCard(0);
					_drawCard->setSelected(false);
				}
				break;
			}
		}
		else if (input == KeyCodes::ENTER_KEY)
		{
			if (_drawCard->getSelected())
			{
				_drawCard->getBehavior()->execute();
			}
			else
			{
				std::shared_ptr<Card> selectedCard = _playerManager->getSelectedPlayer()->getSelectedCard();
				if (selectedCard->getCanBePlayed())
				{
					selectedCard->getBehavior()->execute();
					_playerManager->getSelectedPlayer()->removeSelectedCard();
					// TODO if player has 0 cards on hand and said UNO he won
					_discardPile.push_back(selectedCard);
					_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
				}
				else
				{
					_currentMessage = " SELECTED CARD CAN'T BE PLAYED!";
				}
			}
		}
	}
}

void GameState::drawDisplayNewCardsState(Window& window)
{

}

void GameState::handleInputDisplayNewCardsState()
{

}

void GameState::drawForcedDrawDiscardedState(Window& window)
{

}

void GameState::handleInputForcedDrawDiscardedState()
{
	int input = _getch();

	if (input == KeyCodes::ENTER_KEY)
	{
		// TODO maybe save this behavior reference
		std::shared_ptr<DrawDisplayCardBehavior> drawCard = std::dynamic_pointer_cast<DrawDisplayCardBehavior>(_drawCard->getBehavior());
		for (int i = 0; i < drawCard->getAmount(); ++i)
		{
			std::shared_ptr<Card> drawedCard = VectorHelper::getAndRemoveRandomElement(_discardPile, 1); // TODO typo on drawed???
			if (drawedCard == nullptr)
			{
				// TODO if draw pile also empty, handle it
				drawedCard = _drawPile.back();
				_drawPile.pop_back();
			}
	
			_playerManager->getSelectedPlayer()->addCard(drawedCard);
		}

		endTurn = true;
		_currentState = GameStates::NORMAL;
		_currentMessage = "";
	}
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

void GameState::handleReverseTurnEvent()
{
	_turnDirection = -_turnDirection;
}

void GameState::handleDrawCardEvent(const DrawDisplayCardEvent& eventData)
{
	for (int i = 0; i < eventData.getAmount(); ++i)
	{
		std::shared_ptr<Card> drawedCard = _drawPile.back();
		_drawPile.pop_back();
		_playerManager->getSelectedPlayer()->addCard(drawedCard);

		if (_drawPile.empty())
		{
			if (_discardPile.size() < 2)
			{
				// If there are zero cards in draw pile and only one card on discard pile we'll force a gameover
				// TODO maybe only force a gameover if the player can't play any cards?
			}
			else
			{
				_drawPile = std::move(_discardPile);
				VectorHelper::shuffleVector(_drawPile);
				discardFirstCard();
			}
		}
	}

	endTurn = true;
}

void GameState::handleDrawDiscardedCardEvent(const DrawDiscardedCardEvent& eventData)
{
	_currentState = GameStates::FORCED_DRAW_DISCARD;
	std::shared_ptr<DrawDisplayCardBehavior> drawCard = std::dynamic_pointer_cast<DrawDisplayCardBehavior>(_drawCard->getBehavior());
	drawCard->setAmount(eventData.getAmount());
}

#include "GameState.h"
#include <iostream>
#include <conio.h>
#include "KeyCodes.h"
#include "GoToNextStateEvent.h"
#include "GameOverTransitionData.h"
#include "DrawPileCardBehavior.h"

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
		if (_forcedColor == Colors::WHITE)
		{
			std::cout << " USE A CARD OR DRAW ANOTHER CARD.";
		}
		else
		{
			window.setConsoleColor(_forcedColor);
			std::cout << " USE A CARD OR DRAW ANOTHER CARD."; // TODO print color name
			window.setConsoleColor(Colors::WHITE);
		}
	}

	++nextRow;

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
		EventBus::fireEvent(QuitGameEvent());
		return;
	}

	if (endTurn)
	{
		handleEndTurnInput(input);
	}
	else
	{
		handleNormalTurnInput(input);
	}
}

void GameState::handleEndTurnInput(const int& input)
{
	if (input == KeyCodes::ENTER_KEY)
	{
		if (_forcedColor == Colors::WHITE)
		{
			_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
		}
		else
		{
			_playerManager->selectNextPlayer(_turnDirection, _forcedColor);
		}

		_drawCard->setSelected(false);
		endTurn = false;
	}
}

void GameState::handleNormalTurnInput(const int& input)
{
	if (input == KeyCodes::SPACE)
	{
		handleSayUNOInput();
		return;
	}

	if (input == KeyCodes::ARROW_1 || input == KeyCodes::ARROW_2)
	{
		handleArrowInput();
		return;
	}

	if (input == KeyCodes::ENTER_KEY)
	{
		if (_drawCard->getSelected())
		{
			handleDrawCardInput();
			return;
		}

		tryToUseSelectedCard();
	}
}

void GameState::tryToUseSelectedCard()
{
	std::shared_ptr<Card> selectedCard = _playerManager->getSelectedPlayer()->getSelectedCard();

	if (!selectedCard->getCanBePlayed())
	{
		_currentMessage = " SELECTED CARD CAN'T BE PLAYED!";
		return;
	}

	_forcedColor = Colors::WHITE;

	if (_playerManager->getSelectedPlayer()->getCards().size() == 1)
	{
		useLastPlayerCard(selectedCard);
	}
	else
	{
		useSelectedCard(selectedCard);
	}
}

void GameState::useSelectedCard(std::shared_ptr<Card> selectedCard)
{
	selectedCard->getBehavior()->execute();

	_playerManager->getSelectedPlayer()->removeSelectedCard();
	_discardPile.push_back(selectedCard);

	if (selectedCard->goToNextPlayer())
	{
		_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
	}
}

void GameState::useLastPlayerCard(std::shared_ptr<Card> selectedCard)
{
	_playerManager->getSelectedPlayer()->removeSelectedCard();
	_discardPile.push_back(selectedCard);

	if (_playerManager->getSelectedPlayer()->getSaidUNO())
	{
		GoToNextStateEvent endEvent;
		endEvent.transitionData = std::make_shared<GameOverTransitionData>(_playerManager->getSelectedPlayer()->getName());
		EventBus::fireEvent(endEvent);
	}
	else
	{
		_currentState = GameStates::FORCED_DRAW_PUNISH;
		std::shared_ptr<DrawPileCardBehavior> drawCard = std::dynamic_pointer_cast<DrawPileCardBehavior>(_drawCard->getBehavior());
		drawCard->setAmount(NUMBER_OF_CARDS_TO_PUNISH);
	}
}

void GameState::handleDrawCardInput()
{
	_drawCard->getBehavior()->execute();
	if (_currentState == GameStates::FORCED_DRAW)
	{
		_currentState = GameStates::NORMAL;
	}
}

void GameState::handleArrowInput()
{
	int input = _getch();

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

void GameState::handleSayUNOInput() const
{
	if (_playerManager->getSelectedPlayer()->getCards().size() == 2 || _playerManager->getSelectedPlayer()->getCanSayUNO())
	{
		_playerManager->getSelectedPlayer()->setSaidUNO(true);
	}
}

void GameState::handleInputForcedDrawPunishState()
{
	int input = _getch();

	if (endTurn)
	{
		if (input == KeyCodes::ENTER_KEY)
		{
			std::shared_ptr<Card> usedCard = _discardPile.back();
			usedCard->getBehavior()->execute();

			if (usedCard->goToNextPlayer())
			{
				_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
			}

			_drawCard->setSelected(false);
			endTurn = false;
			_currentState = GameStates::NORMAL;
			_currentMessage = "";

			std::shared_ptr<DrawPileCardBehavior> drawCard = std::dynamic_pointer_cast<DrawPileCardBehavior>(_drawCard->getBehavior());
			drawCard->setAmount(1);
		}
	}
	else
	{
		if (input == KeyCodes::ENTER_KEY)
		{
			_drawCard->getBehavior()->execute();
			endTurn = true;
		}
	}
}

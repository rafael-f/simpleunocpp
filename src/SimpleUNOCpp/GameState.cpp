#include <conio.h>
#include <iostream>
#include "GameState.h"
#include "CardsLoader.h"
#include "KeyCodes.h"
#include "Mediator.h"
#include "PlayerManagerTransitionData.h"
#include "QuitGameEvent.h"
#include "DrawPileCardBehavior.h"
#include "VectorHelper.h"
#include "ReverseTurnCardEvent.h"
#include "SkipTurnCardEvent.h"
#include "SwapHandCardEvent.h"
#include <algorithm>
#include "GoToNextStateEvent.h"
#include "GameOverTransitionData.h"

GameState::GameState()
{
	// TODO move these somewhere else?
	Mediator::registerListener<ReverseTurnCardEvent>([this](const ReverseTurnCardEvent&)
		{
			handleReverseTurnEvent();
		});

	Mediator::registerListener<DrawPileCardEvent>([this](const DrawPileCardEvent& eventData)
		{
			handleDrawCardEvent(eventData);
		});

	Mediator::registerListener<DrawDiscardedCardEvent>([this](const DrawDiscardedCardEvent& eventData)
		{
			handleDrawDiscardedCardEvent(eventData);
		});

	Mediator::registerListener<DrawMoreCardEvent>([this](const DrawMoreCardEvent& eventData)
		{
			handleDrawMoreCardEvent(eventData);
		});

	Mediator::registerListener<SkipTurnCardEvent>([this](const SkipTurnCardEvent&)
		{
			_currentState = GameStates::FORCED_SKIP;
		});

	Mediator::registerListener<SwapHandCardEvent>([this](const SwapHandCardEvent&)
		{
			handleSwapHandCardEvent();
		});

	Mediator::registerListener<WildDrawCardEvent>([this](const WildDrawCardEvent& eventData)
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
		_currentMessage = "YOU DIDN'T SAY UNO, DRAW 2 CARDS";
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

void GameState::addCardToDiscardPile(std::shared_ptr<Card> card)
{
	_discardPile.push_back(card); // TODO ?????
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

// TODO improve this
void GameState::handleInputNormalState()
{
	int input = _getch();

	if (endTurn)
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
		else if (input == KeyCodes::SPACE)
		{
			if(_playerManager->getSelectedPlayer()->getCards().size() == 2 || _playerManager->getSelectedPlayer()->getCanSayUNO())
			{
				_playerManager->getSelectedPlayer()->setSaidUNO(true);
			}
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
				if (_currentState == GameStates::FORCED_DRAW)
				{
					_currentState = GameStates::NORMAL;
				}
			}
			else
			{
				std::shared_ptr<Card> selectedCard = _playerManager->getSelectedPlayer()->getSelectedCard();
				if (selectedCard->getCanBePlayed())
				{
					if (_forcedColor != Colors::WHITE)
					{
						_forcedColor = Colors::WHITE;
					}

					if (_playerManager->getSelectedPlayer()->getCards().size() == 1)
					{
						_playerManager->getSelectedPlayer()->removeSelectedCard();
						_discardPile.push_back(selectedCard);

						if (_playerManager->getSelectedPlayer()->getSaidUNO())
						{
							GoToNextStateEvent endEvent;
							endEvent.transitionData = std::make_shared<GameOverTransitionData>(_playerManager->getSelectedPlayer()->getName());
							Mediator::fireEvent(endEvent);
						}
						else
						{
							_currentState = GameStates::FORCED_DRAW_PUNISH;
							std::shared_ptr<DrawPileCardBehavior> drawCard = std::dynamic_pointer_cast<DrawPileCardBehavior>(_drawCard->getBehavior());
							drawCard->setAmount(NUMBER_OF_CARDS_TO_PUNISH);
						}
					}
					else
					{
						selectedCard->getBehavior()->execute();

						_playerManager->getSelectedPlayer()->removeSelectedCard();
						_discardPile.push_back(selectedCard);

						if (selectedCard->goToNextPlayer())
						{
							_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
						}
					}
				}
				else
				{
					_currentMessage = " SELECTED CARD CAN'T BE PLAYED!";
				}
			}
		}
	}
}

void GameState::handleInputForcedDrawDiscardedState()
{
	int input = _getch();

	if (input == KeyCodes::ENTER_KEY)
	{
		// TODO maybe save this behavior reference
		std::shared_ptr<DrawPileCardBehavior> drawCard = std::dynamic_pointer_cast<DrawPileCardBehavior>(_drawCard->getBehavior());
		for (int i = 0; i < drawCard->getAmount(); ++i)
		{
			std::shared_ptr<Card> drewCard = VectorHelper::getAndRemoveRandomElement(_discardPile, 1);
			if (drewCard == nullptr)
			{
				// TODO if draw pile also empty, handle it
				drewCard = _drawPile.back();
				_drawPile.pop_back();
			}
	
			_playerManager->getSelectedPlayer()->addCard(drewCard);
		}

		endTurn = true;
		_currentState = GameStates::NORMAL;
		_currentMessage = "";
		drawCard->setAmount(1);
	}
}

void GameState::handleInputForcedSkipState()
{
	int input = _getch();

	if (input == KeyCodes::ENTER_KEY)
	{
		_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
		_currentState = GameStates::NORMAL;
	}
}

void GameState::drawSelectPlayerState(Window& window) const
{
	window.setCursorPosition(0, 0);
	std::cout << "SELECT A PLAYER TO SWAP HAND WITH:";

	int row = 2;
	int column = 0;
	int maxLength = window.getConsoleLineLength();

	for (std::shared_ptr<Player> player : _availableSwapHandPlayers)
	{
		column += player->draw(window, row, column);
		if (column + 15 >= maxLength)
		{
			row += 4;
			column = 0;
		}
	}
}

void GameState::handleInputSelectPlayerState()
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
		case KeyCodes::LEFT_ARROW: // TODO make a method
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(false);
			--_swapHandSelectedIndex;
			if (_swapHandSelectedIndex < 0)
			{
				_swapHandSelectedIndex = static_cast<int>(_availableSwapHandPlayers.size()) - 1;
			}
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(true);
			break;
		case KeyCodes::RIGHT_ARROW:
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(false);
			++_swapHandSelectedIndex;
			if (_swapHandSelectedIndex >= _availableSwapHandPlayers.size())
			{
				_swapHandSelectedIndex = 0;
			}
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(true);
			break;
		}
	}
	else if (input == KeyCodes::ENTER_KEY)
	{
		_availableSwapHandPlayers[_swapHandSelectedIndex]->setSelected(false);
		_playerManager->getSelectedPlayer()->getCards().swap(_availableSwapHandPlayers[_swapHandSelectedIndex]->getCards());
		_currentState = GameStates::NORMAL;

		// TODO rule... if the player swapped hand with another that had 1 card in hand he's supposed to be
		// able to UNO with 1 card?
		if (_playerManager->getSelectedPlayer()->getCards().size() == 1)
		{
			_playerManager->getSelectedPlayer()->setCanSayUNO(true);
		}

		if (_availableSwapHandPlayers[_swapHandSelectedIndex]->getCards().size() == 1)
		{
			_availableSwapHandPlayers[_swapHandSelectedIndex]->setCanSayUNO(true);
		}

		_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
	}
}

void GameState::drawSelectColorState(const Window& window) const
{
	int row = 0;
	int column = 0;

	window.setCursorPosition(row, column);
	std::cout << "SELECT A COLOR FOR NEXT CARD:";

	row += 2;
	
	for (std::shared_ptr<ColorPickItem> colorToPick : _colorsToPick)
	{
		column += colorToPick->draw(window, row, column);
	}
}

void GameState::handleInputSelectColorState()
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
		case KeyCodes::LEFT_ARROW: // TODO make a method
			_colorsToPick[_selectedColorIndex]->setSelected(false);
			--_selectedColorIndex;
			if (_selectedColorIndex < 0)
			{
				_selectedColorIndex = static_cast<int>(_colorsToPick.size()) - 1;
			}
			_colorsToPick[_selectedColorIndex]->setSelected(true);
			break;
		case KeyCodes::RIGHT_ARROW:
			_colorsToPick[_selectedColorIndex]->setSelected(false);
			++_selectedColorIndex;
			if (_selectedColorIndex >= _colorsToPick.size())
			{
				_selectedColorIndex = 0;
			}
			_colorsToPick[_selectedColorIndex]->setSelected(true);
			break;
		}
	}
	else if (input == KeyCodes::ENTER_KEY)
	{
		_currentState = GameStates::FORCED_DRAW_WILD;
		_forcedColor = _colorsToPick[_selectedColorIndex]->getSelectedColor();
		_colorsToPick[_selectedColorIndex]->setSelected(false);
		_selectedColorIndex = 0;
		_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
	}
}

void GameState::handleReverseTurnEvent()
{
	_turnDirection = -_turnDirection;
}

void GameState::handleDrawCardEvent(const DrawPileCardEvent& eventData)
{
	_discardPile.back()->setAcceptOnlySameType(false);

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
	std::shared_ptr<DrawPileCardBehavior> drawCard = std::dynamic_pointer_cast<DrawPileCardBehavior>(_drawCard->getBehavior());
	drawCard->setAmount(eventData.getAmount());
}

void GameState::handleDrawMoreCardEvent(const DrawMoreCardEvent& eventData)
{
	std::shared_ptr<DrawPileCardBehavior> drawCard = std::dynamic_pointer_cast<DrawPileCardBehavior>(_drawCard->getBehavior());
	
	if (_currentState != GameStates::FORCED_DRAW)
	{
		drawCard->setAmount(eventData.getAmount());
	}
	else
	{
		drawCard->setAmount(drawCard->getAmount() + eventData.getAmount());
	}

	_currentState = GameStates::FORCED_DRAW;

	_playerManager->getSelectedPlayer()->getSelectedCard()->setAcceptOnlySameType(true);
}

void GameState::handleSwapHandCardEvent()
{
	_currentState = GameStates::SELECT_PLAYER;

	_availableSwapHandPlayers.clear();

	for (std::shared_ptr<Player> player : _playerManager->getPlayers())
	{
		if (player->getName() == _playerManager->getSelectedPlayer()->getName())
		{
			continue;
		}

		_availableSwapHandPlayers.push_back(player);
	}

	_availableSwapHandPlayers[0]->setSelected(true);
	_swapHandSelectedIndex = 0;
}

void GameState::handleWildDrawCardEvent(const WildDrawCardEvent& eventData)
{
	std::shared_ptr<DrawPileCardBehavior> drawCard = std::dynamic_pointer_cast<DrawPileCardBehavior>(_drawCard->getBehavior());

	if (_currentState == GameStates::NORMAL)
	{
		drawCard->setAmount(eventData.getAmount());
	}
	else
	{
		drawCard->setAmount(drawCard->getAmount() + eventData.getAmount());
	}

	_currentState = GameStates::SELECT_COLOR;
	_selectedColorIndex = 0;
	_colorsToPick[0]->setSelected(true);
}

void GameState::handleInputForcedDrawWildState()
{
	int input = _getch();

	if (endTurn)
	{
		if (input == KeyCodes::ENTER_KEY)
		{
			_playerManager->selectNextPlayer(_turnDirection, _forcedColor);
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

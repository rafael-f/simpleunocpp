#include "GameState.h"
#include <iostream>
#include <conio.h>
#include "KeyCodes.h"
#include "DrawPileCardBehavior.h"

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

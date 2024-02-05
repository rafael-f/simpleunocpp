#include "GameState.h"
#include <conio.h>
#include "KeyCodes.h"
#include "DrawPileCardBehavior.h"
#include "VectorHelper.h"

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

void GameState::handleDrawDiscardedCardEvent(const DrawDiscardedCardEvent& eventData)
{
	_currentState = GameStates::FORCED_DRAW_DISCARD;
	std::shared_ptr<DrawPileCardBehavior> drawCard = std::dynamic_pointer_cast<DrawPileCardBehavior>(_drawCard->getBehavior());
	drawCard->setAmount(eventData.getAmount());
}
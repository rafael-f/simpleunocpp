#include "GameState.h"
#include "VectorHelper.h"

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

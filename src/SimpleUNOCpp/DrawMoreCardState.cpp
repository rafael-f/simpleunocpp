#include "GameState.h"
#include "DrawPileCardBehavior.h"

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

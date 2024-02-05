#include "GameState.h"
#include <conio.h>
#include "KeyCodes.h"

void GameState::handleInputForcedSkipState()
{
	int input = _getch();

	if (input == KeyCodes::ENTER_KEY)
	{
		_playerManager->selectNextPlayer(_turnDirection, _discardPile.back());
		_currentState = GameStates::NORMAL;
	}
}

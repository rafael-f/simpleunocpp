#include "GameState.h"

void GameState::handleReverseTurnEvent()
{
	_turnDirection = -_turnDirection;
}

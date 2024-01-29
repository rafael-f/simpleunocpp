#include "GameState.h"
#include <iostream>
#include "QuitGameEvent.h"
#include "Mediator.h"
#include "PlayerManagerTransitionData.h"
#include <conio.h>
#include "KeyCodes.h"

void GameState::draw(Window& window)
{
	window.showPrompt(false);

	for (auto const& player : _playerManager->getplayers())
	{
		std::cout << player->getName() << std::endl;
	}
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
}

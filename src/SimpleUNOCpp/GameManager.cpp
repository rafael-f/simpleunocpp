#include "GameManager.h"

GameManager::GameManager()
{
	_window = std::make_unique<Window>();

	_inputManager = std::make_unique<InputManager>();

	_stateManager = std::make_unique<StateManager>();

	_playerManager = std::make_unique<PlayerManager>();
}

void GameManager::start()
{
	if (!_loaded)
	{
		load();
	}

	_stateManager->setState(0);
}

void GameManager::run()
{
	while (_window->isOpen())
	{
		_stateManager->Draw(*_window);

		_inputManager->handleInput();
		
		// TODO update
		break;
	}
}

void GameManager::load()
{
	// TODO load game rules
	// TODO load cards
	_loaded = true;
}

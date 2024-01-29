#include "GameManager.h"

GameManager::GameManager()
{
	_window = std::make_unique<Window>();

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

	run();
}

void GameManager::run()
{
	while (_window->isOpen())
	{
		_window->clear();

		_stateManager->Draw(*_window);

		_stateManager->handleInput();
	}
}

void GameManager::load()
{
	// TODO load game rules
	// TODO load cards
	_loaded = true;
}

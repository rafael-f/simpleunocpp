#pragma once
#include <memory>
#include "Window.h"
#include "StateManager.h"
#include "PlayerManager.h"

// The GameManager is responsible for initial loading and running the game loop.
class GameManager
{
public:
	GameManager();

	void start();

private:
	void run();

	void load();

	std::unique_ptr<Window> _window;

	std::unique_ptr<StateManager> _stateManager;

	std::unique_ptr<PlayerManager> _playerManager;

	bool _loaded = false;
};

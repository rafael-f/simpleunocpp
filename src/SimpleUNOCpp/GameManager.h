#pragma once
#include <memory>
#include "Window.h"
#include "InputManager.h"
#include "StateManager.h"
#include "PlayerManager.h"

class GameManager
{
public:
	GameManager();

	void start();

private:
	void run();

	void load();

	std::unique_ptr<Window> _window;

	std::unique_ptr<InputManager> _inputManager;

	std::unique_ptr<StateManager> _stateManager;

	std::unique_ptr<PlayerManager> _playerManager;
};
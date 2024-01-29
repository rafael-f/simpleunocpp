#pragma once
#include "Window.h"
#include <string>

// Interface for game states.
class State
{
public:
	virtual void draw(const Window& window) = 0;

	virtual void handleInput() = 0;

	virtual ~State() = default;
};

#pragma once
#include "Window.h"

class State
{
public:
	virtual void draw(Window& window) = 0;

	virtual ~State() = default;
};

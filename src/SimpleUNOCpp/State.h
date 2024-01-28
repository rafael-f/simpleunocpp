#pragma once
#include "Window.h"
#include <string>

class State
{
public:
	virtual void draw() = 0;

	virtual ~State() = default;

	virtual void handleInput(const std::string& input) = 0;
};

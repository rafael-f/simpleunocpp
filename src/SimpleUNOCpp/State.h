#pragma once
#include "Window.h"
#include <string>
#include "TransitionData.h"
#include <memory>

// Interface for game states.
class State
{
public:
	// TODO does it make sense to always pass window? can this be improved?
	virtual void draw(Window& window) = 0;

	virtual void handleInput() = 0;

	virtual ~State() = default;

	virtual void setData(std::shared_ptr<TransitionData> transitionData) = 0;
};

#pragma once
#include "Event.h"
#include "TransitionData.h"
#include <memory>

// Event to fire to change state.
struct GoToNextStateEvent : public Event
{
	std::shared_ptr<TransitionData> transitionData;
};

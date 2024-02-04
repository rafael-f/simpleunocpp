#pragma once
#include "Event.h"
#include "TransitionData.h"
#include <memory>

// Event to fire to change state.
struct GoToFirstStateEvent : public Event
{
	std::shared_ptr<TransitionData> transitionData;
};

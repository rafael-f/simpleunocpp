#pragma once
#include "Event.h"

// Fire this event to show or hide the prompt.
struct ShowPromptEvent : public Event
{
	bool showPrompt;
};

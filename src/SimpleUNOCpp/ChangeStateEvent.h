#pragma once
#include "Event.h"

struct ChangeStateEvent : public Event
{
	int nextState;
};

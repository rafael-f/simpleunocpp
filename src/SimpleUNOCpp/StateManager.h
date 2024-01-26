#pragma once
#include <vector>
#include <memory>
#include "State.h"

class StateManager
{
private:
	std::vector<std::unique_ptr<State>> _states;
};

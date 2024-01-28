#include "Mediator.h"

std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> Mediator::eventListeners;

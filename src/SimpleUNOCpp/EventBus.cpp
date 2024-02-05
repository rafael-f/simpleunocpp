#include "EventBus.h"

std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> EventBus::eventListeners;

void EventBus::clearListeners()
{
	eventListeners.clear();
}

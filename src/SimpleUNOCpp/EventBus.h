#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include "Event.h"

// EventBus to allow objects to communicate without direct dependency of each other.
class EventBus
{
public:
    // Register a listener for a specific event type
    template <typename EventType>
    static void registerListener(const std::function<void(const EventType&)>& listener)
    {
        std::string eventName = typeid(EventType).name();

        eventListeners[eventName].emplace_back([listener](const Event& event)
            {
                listener(static_cast<const EventType&>(event));
            });
    }

    // Trigger an event
    template <typename EventType>
    static void fireEvent(const EventType& eventData) {
        std::string eventName = typeid(EventType).name();

        auto listenersIt = eventListeners.find(eventName);

        if (listenersIt != eventListeners.end())
        {
            for (const auto& listener : listenersIt->second) {
                listener(eventData);
            }
        }
    }

    static void clearListeners();

private:
    static std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> eventListeners;

    EventBus() = default;
};

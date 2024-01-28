#pragma once
#include "QuitGameEvent.h"

// Represents the app window.
class Window
{
public:
	Window();

	bool isOpen() const;

	void clear() const;

private:
	void handleQuitGameEvent(const QuitGameEvent& quitGameEvent);

	bool _isOpen = true;

	void hidePrompt() const;
};

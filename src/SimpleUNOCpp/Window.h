#pragma once
#include "QuitGameEvent.h"
#include "ShowPromptEvent.h"

// Represents the app window.
class Window
{
public:
	Window();

	bool isOpen() const;

	void clear() const;

	void setCursorPosition(const int& row, const int& column) const;

private:
	void handleQuitGameEvent(const QuitGameEvent& quitGameEvent);

	bool _isOpen = true;

	void showPrompt(const bool& show) const;

	void handleShowPromptEvent(const ShowPromptEvent& showPromptEvent) const;
};

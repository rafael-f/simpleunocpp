#pragma once
#include <string>
#include "QuitGameEvent.h"
#include "ShowPromptEvent.h"
#include "Colors.h"

// Represents the app window.
class Window
{
public:
	Window();

	bool isOpen() const;

	void clear() const;

	void setCursorPosition(const int& row, const int& column) const;

	void showPrompt(const bool& show);

	void setConsoleColor(Colors color) const;

	static std::string fillWithSpaces(const std::string& input, std::size_t minWidth);

	int getConsoleLineLength() const;

private:
	void handleQuitGameEvent(const QuitGameEvent& quitGameEvent);

	bool _isOpen = true;

	void handleShowPromptEvent(const ShowPromptEvent& showPromptEvent);

	bool _showingPrompt = true;
};

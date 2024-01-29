#include "Window.h"
#include "Mediator.h"
#include <Windows.h>

Window::Window()
{
	Mediator::registerListener<QuitGameEvent>([this](const QuitGameEvent& eventData)
		{
			handleQuitGameEvent(eventData);
		});

	Mediator::registerListener<ShowPromptEvent>([this](const ShowPromptEvent& eventData)
		{
			handleShowPromptEvent(eventData);
		});

	showPrompt(false);
}

bool Window::isOpen() const
{
	return _isOpen;
}

void Window::clear() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	COORD topLeft = { 0, 0 };
	DWORD written;
	FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X * csbi.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, topLeft, &written);

	SetConsoleCursorPosition(hConsole, topLeft);
}

void Window::handleQuitGameEvent(const QuitGameEvent&)
{
	_isOpen = false;
}

void Window::showPrompt(const bool& show)
{
	if (_showingPrompt != show)
	{
		_showingPrompt = show;
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(consoleHandle, &cursorInfo);

		cursorInfo.bVisible = show;
		SetConsoleCursorInfo(consoleHandle, &cursorInfo);
	}
}

void Window::handleShowPromptEvent(const ShowPromptEvent& showPromptEvent)
{
	showPrompt(showPromptEvent.showPrompt);
}

void Window::setCursorPosition(const int& row, const int& column) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD cursorPos;
	cursorPos.X = static_cast<short>(column);
	cursorPos.Y = static_cast<short>(row);

	SetConsoleCursorPosition(hConsole, cursorPos);
}

#include "Window.h"
#include "Mediator.h"
#include <Windows.h>

Window::Window()
{
	Mediator::registerListener<QuitGameEvent>([this](const QuitGameEvent& eventData)
		{
			handleQuitGameEvent(eventData);
		});

	hidePrompt();
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

void Window::hidePrompt() const
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);

	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

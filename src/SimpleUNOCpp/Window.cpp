#include <iomanip>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include "Window.h"
#include "Mediator.h"

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

void Window::setConsoleColor(Colors color) const
{
	int colorValue;

	switch (color)
	{
	case Colors::RED:
		colorValue = FOREGROUND_RED;
		break;
	case Colors::BLUE:
		colorValue = FOREGROUND_BLUE;
		break;
	case Colors::YELLOW:
		colorValue = FOREGROUND_RED | FOREGROUND_GREEN;
		break;
	case Colors::GREEN:
		colorValue = FOREGROUND_GREEN;
		break;
	default:
		colorValue = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(colorValue));
}

std::string Window::fillWithSpaces(const std::string& input, std::size_t minWidth)
{
	std::ostringstream oss;
	std::size_t padding = (minWidth - input.size()) / 2;
	oss << std::setw(padding + input.size()) << std::right << input;
	while (oss.str().size() < minWidth)
	{
		oss << " ";
	}

	return oss.str();
}

int Window::getConsoleLineLength() const
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

#include <conio.h>
#include <fstream>
#include <iostream>
#include "MenuState.h"
#include "Mediator.h"
#include "GoToNextStateEvent.h"
#include "KeyCodes.h"

const std::string MenuState::TITLE_FILE_PATH = "assets/unotitle.txt";

MenuState::MenuState()
{
	loadTitleLines();
}

void MenuState::draw(Window& window)
{
	for (std::string line : _titleLines)
	{
		std::cout << line << std::endl;
	}
}

void MenuState::handleInput()
{
	int input = _getch();

	if (input == KeyCodes::ENTER_KEY)
	{
		GoToNextStateEvent changeStateEvent;
		Mediator::fireEvent(changeStateEvent);
	}
}

void MenuState::loadTitleLines()
{
	std::ifstream reader(TITLE_FILE_PATH);

	std::string lineFromFile;

	while (std::getline(reader, lineFromFile))
	{
		_titleLines.push_back(lineFromFile);
	}
}

void MenuState::setData(std::shared_ptr<TransitionData>)
{
	// Doesn't need data
}

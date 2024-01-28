#include "MenuState.h"
#include "Mediator.h"
#include "GoToNextStateEvent.h"
#include <fstream>
#include <iostream>

const std::string MenuState::TITLE_FILE_PATH = "assets/unotitle.txt";

MenuState::MenuState()
{
	loadTitleLines();
}

void MenuState::draw()
{
	for (std::string line : _titleLines)
	{
		std::cout << line << std::endl;
	}
}

void MenuState::handleInput(const std::string&)
{
	GoToNextStateEvent changeStateEvent;

	Mediator::fireEvent(changeStateEvent);
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

#include "MenuState.h"
#include "Mediator.h"
#include "ChangeStateEvent.h"
#include <iostream>

MenuState::MenuState()
{

}

void MenuState::draw()
{
	std::cout << "menu" << std::endl;
}

void MenuState::handleInput(const std::string&)
{
	ChangeStateEvent changeStateEvent;
	changeStateEvent.nextState = 1;

	Mediator::fireEvent(changeStateEvent);
}

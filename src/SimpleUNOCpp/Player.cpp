#include "Player.h"
#include <iostream>
#include "KeyCodes.h"

void Player::setName(const std::string& name)
{
	_name = name;
	_nameLength = static_cast<int>(_name.length());
}

std::string Player::getName() const
{
	return _name;
}

void Player::updateCardStates(const Card& cardOnTop)
{

}

void Player::addCard(std::shared_ptr<Card> card)
{
	_cardsOnHand.push_back(card);
}

int Player::draw(Window& window, const int& row, const int& column) const
{
	window.setCursorPosition(row, column);

	std::string cardsCountLine = std::to_string(_cardsOnHand.size()) + " cards";
	int maxSize = cardsCountLine.length() > _nameLength ? static_cast<int>(cardsCountLine.length()) : _nameLength;

	if (_isSelected)
	{
		std::cout << KeyCodes::TOP_LEFT_CORNER;
		for (int i = 0; i < maxSize; ++i)
		{
			std::cout << KeyCodes::HORIZONTAL_LINE;
		}
		std::cout << KeyCodes::TOP_RIGHT_CORNER << std::endl;
	}
	else
	{
		std::cout << std::endl;
	}

	window.setCursorPosition(row + 1, column);

	if (_isSelected)
	{
		std::string asd = Window::fillWithSpaces(_name, maxSize);
		std::cout << KeyCodes::VERTICAL_LINE << Window::fillWithSpaces(_name, maxSize) << KeyCodes::VERTICAL_LINE << std::endl;
	}
	else
	{
		std::cout << " " << Window::fillWithSpaces(_name, maxSize) << " " << std::endl;
	}

	window.setCursorPosition(row + 2, column);

	if (_isSelected)
	{
		std::cout << KeyCodes::VERTICAL_LINE << Window::fillWithSpaces(cardsCountLine, maxSize) << KeyCodes::VERTICAL_LINE << std::endl;
	}
	else
	{
		std::cout << " " << Window::fillWithSpaces(cardsCountLine, maxSize) << " " << std::endl;
	}

	window.setCursorPosition(row + 3, column);

	if (_isSelected)
	{
		std::cout << KeyCodes::BOTTOM_LEFT_CORNER;
		for (int i = 0; i < maxSize; ++i)
		{
			std::cout << KeyCodes::HORIZONTAL_LINE;
		}
		std::cout << KeyCodes::BOTTOM_RIGHT_CORNER << std::endl;
	}
	else
	{
		std::cout << std::endl;
	}

	return maxSize + 2;
}

void Player::setSelected(const bool& selected)
{
	_isSelected = selected;
}

void Player::drawCards(Window& window, const int& row) const
{
	_cardsOnHand[0]->setSelected(true);

	int column = 0;
	for (auto card : _cardsOnHand)
	{
		card->draw(row, column, window);
		column += 11;
	}
}

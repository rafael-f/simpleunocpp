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

void Player::updateCardStates(std::shared_ptr<Card> cardOnTop) const
{
	if (cardOnTop->getAcceptOnlySameType())
	{
		for (std::shared_ptr<Card> card : _cardsOnHand)
		{
			card->setCanBePlayed(cardOnTop->checkCanBePlayed(card));
		}
	}
	else
	{
		Colors topColor = cardOnTop->getColor();
		for (std::shared_ptr<Card> card : _cardsOnHand)
		{
			Colors cardColor = card->getColor();
			bool canBePlayed = cardColor == topColor || cardColor == Colors::WHITE || topColor == Colors::WHITE; // TODO if top discard is white can others be used on top of it?
			if (!canBePlayed)
			{
				canBePlayed = card->checkCanBePlayed(cardOnTop);
			}

			card->setCanBePlayed(canBePlayed);
		}
	}
}

void Player::updateCardStates(const Colors& color) const
{
	for (std::shared_ptr<Card> card : _cardsOnHand)
	{
		Colors cardColor = card->getColor();
		card->setCanBePlayed(cardColor == color || cardColor == Colors::WHITE);
	}
}

void Player::addCard(std::shared_ptr<Card> card)
{
	_cardsOnHand.push_back(card);
	_saidUNO = false;
	_canSayUNO = false;
}

void Player::removeSelectedCard()
{
	_cardsOnHand[_selectedCardIndex]->setSelected(false);
	_cardsOnHand.erase(_cardsOnHand.begin() + _selectedCardIndex);
	_selectedCardIndex = 0;
	if (!_cardsOnHand.empty())
	{
		_cardsOnHand[_selectedCardIndex]->setSelected(true);
	}
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
		std::cout << KeyCodes::VERTICAL_LINE; // TODO save the LINE in a char instead
		if (_saidUNO)
		{
			window.setConsoleColor(Colors::GREEN);
			std::cout << Window::fillWithSpaces("UNO", maxSize);
			window.setConsoleColor(Colors::WHITE);
		}
		else
		{
			std::cout << Window::fillWithSpaces(" ", maxSize);
		}
		std::cout << KeyCodes::VERTICAL_LINE << std::endl;
	}
	else
	{
		std::cout << " ";
		if (_saidUNO)
		{
			window.setConsoleColor(Colors::GREEN);
			std::cout << Window::fillWithSpaces("UNO", maxSize);
			window.setConsoleColor(Colors::WHITE);
		}
		else
		{
			std::cout << Window::fillWithSpaces(" ", maxSize);
		}
		std::cout << " " << std::endl;
	}

	window.setCursorPosition(row + 4, column);

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

void Player::drawCards(Window& window, int& row) const
{
	window.setCursorPosition(row, 0);
	std::cout << _name << " HAND:";
	++row;

	int column = 0;
	for (auto card : _cardsOnHand)
	{
		card->draw(row, column, window);
		column += 11;
		if (column + 11 >= window.getConsoleLineLength())
		{
			row += 6;
			column = 0;
		}
	}
}

void Player::setSelectedCard(const int& index)
{
	if (_selectedCardIndex <= _cardsOnHand.size() && !_cardsOnHand.empty())
	{
		_cardsOnHand[_selectedCardIndex]->setSelected(false);
	}

	if (index != -1) // TODO use a bool instead?
	{
		_selectedCardIndex = index;
		_cardsOnHand[_selectedCardIndex]->setSelected(true);
	}
}

std::shared_ptr<Card> Player::getSelectedCard()
{
	return _cardsOnHand[_selectedCardIndex];
}

void Player::selectCard(const int& offset)
{
	int nextIndex = _selectedCardIndex + offset;
	if (nextIndex < 0)
	{
		nextIndex = static_cast<int>(_cardsOnHand.size()) - 1;
	}
	else if (nextIndex >= _cardsOnHand.size())
	{
		nextIndex = 0;
	}

	setSelectedCard(nextIndex);
}

void Player::setSaidUNO(const bool& saidUNO)
{
	_saidUNO = saidUNO;
}

bool Player::getSaidUNO() const
{
	return _saidUNO;
}

std::vector<std::shared_ptr<Card>>& Player::getCards()
{
	return _cardsOnHand;
}

void Player::setCanSayUNO(const bool& canSay)
{
	_canSayUNO = canSay;
}

bool Player::getCanSayUNO() const
{
	return _canSayUNO;
}

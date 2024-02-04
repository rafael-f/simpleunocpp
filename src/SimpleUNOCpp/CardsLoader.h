#pragma once
#include <memory>
#include <vector>
#include "Card.h"

// Loads the game cards.
class CardsLoader
{
public:
	static void createCards(std::vector<std::shared_ptr<Card>>& _cardsHolder);

private:
	static const int NUMBER_OF_NORMAL_CARDS = 2; // todo read all these values from files
	static const int NORMAL_CARDS_START = 0;
	static const int NORMAL_CARDS_END = 9;

	static const int NUMBER_OF_DRAW_MORE_CARDS = 2;
	static const int DRAW_MORE_AMOUNT = 2;

	static const int NUMBER_OF_REVERSE_CARDS = 2;

	static const int NUMBER_OF_SKIP_CARDS = 2;

	static const int NUMBER_OF_WILD_DRAW_CARDS = 4;
	static const int WILD_DRAW_AMOUNT = 4;

	static const int NUMBER_OF_DRAW_DISCARDED = 1;
	static const int DRAW_DISCARDED_AMOUNT = 2;

	static const int NUMBER_OF_SWAP_HANDS = 4;
};

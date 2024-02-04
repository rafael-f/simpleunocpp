#include "CardsLoader.h"
#include "DrawDiscardedCardBehavior.h"
#include "DrawMoreCardBehavior.h"
#include "NormalCardBehavior.h"
#include "ReverseTurnCardBehavior.h"
#include "SkipTurnCardBehavior.h"
#include "SwapHandCardBehavior.h"
#include "VectorHelper.h"
#include "WildDrawCardBehavior.h"

// TODO this should be using factory(s)... and loading data from files...
void CardsLoader::createCards(std::vector<std::shared_ptr<Card>>& _cardsHolder)
{
	// Most cards follow the rule of existing for all 4 colors, we'll create all of them in a loop.
	for (int c = static_cast<int>(Colors::RED); c < static_cast<int>(Colors::WHITE); ++c)
	{
		Colors color = static_cast<Colors>(c);

		// Create normal cards
		for (int n = 0; n < NUMBER_OF_NORMAL_CARDS; ++n)
		{
			for (int i = NORMAL_CARDS_START; i <= NORMAL_CARDS_END; ++i)
			{
				std::shared_ptr<NormalCardBehavior> cardBehavior = std::make_shared<NormalCardBehavior>(i);
				std::shared_ptr<Card> card = std::make_shared<Card>(color, cardBehavior);
				_cardsHolder.push_back(card);
			}
		}

		// Create draw more cards
		for (int n = 0; n < NUMBER_OF_DRAW_MORE_CARDS; ++n)
		{
			std::shared_ptr<DrawMoreCardBehavior> cardBehavior = std::make_shared<DrawMoreCardBehavior>(DRAW_MORE_AMOUNT);
			std::shared_ptr<Card> card = std::make_shared<Card>(color, cardBehavior);
			_cardsHolder.push_back(card);
		}

		// Create reverse turn cards
		for (int n = 0; n < NUMBER_OF_REVERSE_CARDS; ++n)
		{
			std::shared_ptr<ReverseTurnCardBehavior> cardBehavior = std::make_shared<ReverseTurnCardBehavior>();
			std::shared_ptr<Card> card = std::make_shared<Card>(color, cardBehavior);
			_cardsHolder.push_back(card);
		}

		// Create skip cards
		for (int n = 0; n < NUMBER_OF_SKIP_CARDS; ++n)
		{
			std::shared_ptr<SkipTurnCardBehavior> cardBehavior = std::make_shared<SkipTurnCardBehavior>();
			std::shared_ptr<Card> card = std::make_shared<Card>(color, cardBehavior);
			_cardsHolder.push_back(card);
		}

		// Create draw from discard pile cards
		for (int n = 0; n < NUMBER_OF_DRAW_DISCARDED; ++n)
		{
			std::shared_ptr<DrawDiscardedCardBehavior> cardBehavior = std::make_shared<DrawDiscardedCardBehavior>(DRAW_DISCARDED_AMOUNT);
			std::shared_ptr<Card> card = std::make_shared<Card>(color, cardBehavior);
			_cardsHolder.push_back(card);
		}
	}

	// Create wild draw cards
	for (int n = 0; n < NUMBER_OF_WILD_DRAW_CARDS; ++n)
	{
		std::shared_ptr<WildDrawCardBehavior> cardBehavior = std::make_shared<WildDrawCardBehavior>(WILD_DRAW_AMOUNT);
		std::shared_ptr<Card> card = std::make_shared<Card>(Colors::WHITE, cardBehavior);
		_cardsHolder.push_back(card);
	}

	// Create swap hands cards
	for (int n = 0; n < NUMBER_OF_SWAP_HANDS; ++n)
	{
		std::shared_ptr<SwapHandCardBehavior> cardBehavior = std::make_shared<SwapHandCardBehavior>();
		std::shared_ptr<Card> card = std::make_shared<Card>(Colors::WHITE, cardBehavior);
		_cardsHolder.push_back(card);
	}

	VectorHelper::shuffleVector(_cardsHolder);
}

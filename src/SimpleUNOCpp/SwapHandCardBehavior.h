#pragma once
#include "CardBehavior.h"

// This card will swap the hands of 2 players.
class SwapHandCardBehavior : public CardBehavior
{
public:
	SwapHandCardBehavior();

	void execute() override;

	std::string& getSymbolToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

	std::string getNameToDraw() override;

	bool getGoToNextPlayer() override;

private:
	std::string _symbolToDraw;

	static const std::string NAME_TO_DRAW;
};

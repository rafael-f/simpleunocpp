#pragma once
#include "CardBehavior.h"

// This card skips the turn of the next player.
class SkipTurnCardBehavior : public CardBehavior
{
public:
	SkipTurnCardBehavior();

	void execute() override;

	std::string& getSymbolToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

	std::string getNameToDraw() override;

	bool getGoToNextPlayer() override;

private:
	std::string _symbolToDraw;

	static const std::string NAME_TO_DRAW;
};

#pragma once
#include "CardBehavior.h"

// This card will reverse the order that players play.
class ReverseTurnCardBehavior : public CardBehavior
{
public:
	ReverseTurnCardBehavior();

	void execute() override;

	std::string& getSymbolToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

	std::string getNameToDraw() override;

private:
	std::string _symbolToDraw;

	static const std::string NAME_TO_DRAW;
};

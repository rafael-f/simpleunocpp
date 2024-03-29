#pragma once
#include "CardBehavior.h"

// This behavior forces the player to draw more cards from the draw pile.
class DrawMoreCardBehavior : public CardBehavior
{
public:
	explicit DrawMoreCardBehavior(const int& drawMoreAmount);

	void execute() override;

	std::string& getSymbolToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

	std::string getNameToDraw() override;

	bool getGoToNextPlayer() override;

private:
	int _drawMoreAmount;

	std::string _symbolToDraw;
};

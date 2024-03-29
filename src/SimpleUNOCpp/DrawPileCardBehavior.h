#pragma once
#include "CardBehavior.h"

// Card used on top of the draw pile to allow the player to draw cards.
class DrawPileCardBehavior : public CardBehavior
{
public:
	DrawPileCardBehavior();

	void execute() override;

	std::string& getSymbolToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

	void setAmount(const int& amount);

	std::string getNameToDraw() override;

	int getAmount() const;

	bool getGoToNextPlayer() override;

private:
	static const std::string DRAW_NAME;

	int _amount;

	std::string _symbolToDraw;
};

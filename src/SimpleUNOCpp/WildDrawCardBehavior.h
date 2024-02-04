#pragma once
#include "CardBehavior.h"

class WildDrawCardBehavior : public CardBehavior
{
public:
	explicit WildDrawCardBehavior(const int& drawAmount);

	void execute() override;

	std::string& getSymbolToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

	std::string getNameToDraw() override;

	bool getGoToNextPlayer() override;

private:
	int _drawAmount;

	std::string _symbolToDraw;
};

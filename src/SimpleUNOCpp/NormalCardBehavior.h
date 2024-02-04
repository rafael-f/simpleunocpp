#pragma once
#include "CardBehavior.h"

// A normal card, doesn't have any special effects.
class NormalCardBehavior : public CardBehavior
{
public:
	explicit NormalCardBehavior(int value);

	void execute() override;

	std::string& getSymbolToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

	int getValue() const;

	std::string getNameToDraw() override;

	bool getGoToNextPlayer() override;

private:
	int _value;

	std::string _symbolToDraw;
};

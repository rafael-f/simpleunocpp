#pragma once
#include "CardBehavior.h"

class WildDrawCardBehavior : public CardBehavior
{
public:
	explicit WildDrawCardBehavior(const int& drawAmount);

	void execute() override;

	std::string& getStringToDraw() override;

	bool checkCanBePlayed(std::shared_ptr<CardBehavior> otherBehavior) override;

private:
	int _drawAmount;

	std::string _stringToDraw;
};

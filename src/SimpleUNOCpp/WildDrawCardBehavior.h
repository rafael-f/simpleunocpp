#pragma once
#include "CardBehavior.h"

class WildDrawCardBehavior : public CardBehavior
{
public:
	explicit WildDrawCardBehavior(const int& drawAmount);

	void execute() override;

	std::string& getStringToDraw() override;

private:
	int _drawAmount;

	std::string _stringToDraw;
};

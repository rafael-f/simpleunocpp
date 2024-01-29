#pragma once
#include "CardBehavior.h"

// A normal card, doesn't have any special effects.
class NormalCardBehavior : public CardBehavior
{
public:
	NormalCardBehavior(int value);

	void execute() override;

	std::string& getStringToDraw() override;

private:
	int _value;

	std::string _stringToDraw;
};

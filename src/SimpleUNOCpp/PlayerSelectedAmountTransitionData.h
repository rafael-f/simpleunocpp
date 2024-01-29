#pragma once
#include "TransitionData.h"

class PlayerSelectedAmountTransitionData : public TransitionData
{
public:
	PlayerSelectedAmountTransitionData(int amount) : selectedAmount(amount)
	{
	}

	int selectedAmount;
};

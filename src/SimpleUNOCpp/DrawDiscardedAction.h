#pragma once
#include "TurnAction.h"

class DrawDiscardedAction : public TurnAction
{
public:
	DrawDiscardedAction(const int& amount);

private:
	int _amount;
};

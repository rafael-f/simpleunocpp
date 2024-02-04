#pragma once
#include "TransitionData.h"
#include <string>

class GameOverTransitionData : public TransitionData
{
public:
	explicit GameOverTransitionData(std::string winnerName);

	std::string _winnerName;
};

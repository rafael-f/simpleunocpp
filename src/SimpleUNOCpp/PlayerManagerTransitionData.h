#pragma once
#include "TransitionData.h"
#include <memory>
#include "PlayerManager.h"

class PlayerManagerTransitionData : public TransitionData
{
public:
	explicit PlayerManagerTransitionData(std::shared_ptr<PlayerManager> playerManager) : playerManager(playerManager)
	{
	}

	std::shared_ptr<PlayerManager> playerManager;
};

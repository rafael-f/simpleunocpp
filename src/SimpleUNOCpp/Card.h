#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>
#include "CardBehavior.h"

// A card contains many card behaviors that can all alter something in gameplay.
class Card : public GameObject
{
private:
	std::vector<std::shared_ptr<CardBehavior>> _behaviors;
};

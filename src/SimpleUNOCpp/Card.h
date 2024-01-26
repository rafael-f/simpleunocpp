#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>
#include "CardBehavior.h"

class Card : public GameObject
{
private:
	std::vector<std::shared_ptr<CardBehavior>> _behaviors;
};

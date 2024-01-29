#pragma once
#include <vector>
#include <memory>
#include "Card.h"

class VectorHelper
{
public:
	static void shuffleCardsVector(std::vector<std::shared_ptr<Card>>& vector);
};

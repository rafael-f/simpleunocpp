#include "VectorHelper.h"
#include <algorithm>
#include <random>

void VectorHelper::shuffleCardsVector(std::vector<std::shared_ptr<Card>>& vector)
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(vector.begin(), vector.end(), g);
}

#pragma once
#include <algorithm>
#include <memory>
#include <vector>
#include <random>

class VectorHelper
{
public:
	template <typename T>
	static void shuffleVector(std::vector<std::shared_ptr<T>>& vector)
	{
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(vector.begin(), vector.end(), g);
	}
};

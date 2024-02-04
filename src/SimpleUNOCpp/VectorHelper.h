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

	template <typename T>
	static T getAndRemoveRandomElement(std::vector<T>& vector, const int& trimAmount)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		int length = vector.size() - 1 - trimAmount;
		if (length < 0)
		{
			return nullptr;
		}

		std::uniform_int_distribution<> distrib(0, length);

		int randomIndex = distrib(gen);

		T randomElement = vector[randomIndex];

		vector.erase(vector.begin() + randomIndex);

		return randomElement;
	}
};

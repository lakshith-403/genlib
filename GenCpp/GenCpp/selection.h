#pragma once
#include <vector>
class selection
{
public:
	static void initPopulation(std::vector<std::pair<double, int>>& population);
	static std::vector<std::pair<int, int>> roulette_wheel_selection(std::vector<std::pair<double, int>> population, int parentSize);
	static std::vector<std::pair<int, int>> stochastic_universal_sampling(std::vector<std::pair<double, int>> population, int parentSize);
};


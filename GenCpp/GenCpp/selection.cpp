#include "selection.h"
#include <vector>
#include "util.h"

/// <summary>
///	Initializing the fitnesses of the population as percentages before running selection algorithms
/// </summary>
/// <param name="population"></param>
void selection::initPopulation(std::vector<std::pair<double, int>>& population) {
	double totalPerc = 0;
	for (std::pair<double, int>& p : population)
		totalPerc += p.first;
	for (size_t i = 0; i < population.size(); i++) {
		population[i].first = population[i].first / totalPerc * 100.0;
	}
}

/// <summary>
/// Roulette Wheel Selection
/// </summary>
/// <param name="population"></param>
/// <param name="parentSize"></param>
/// <returns></returns>
std::vector<std::pair<int, int>> selection::roulette_wheel_selection(std::vector<std::pair<double, int>> population, int parentSize) {
	int amount = population.size();

	initPopulation(population);

	double totalPerc = 0;
	for (int i = 0; i < amount; i++) {
		population[i].first += totalPerc;
		totalPerc = population[i].first;
	}

	std::vector<std::pair<int, int>> parents;
	for (int i = 0; i < parentSize; i++) {
		std::pair<int, int> parent;
		std::vector<std::pair<double, int>>::iterator itr;
		double randNum;

		randNum = util::rand(0, (int)totalPerc - 1);
		itr = std::lower_bound(population.begin(), population.end(), std::make_pair((double)randNum, -1));
		parent.first = itr->second;

		randNum = util::rand(0, (int)totalPerc - 1);
		itr = std::lower_bound(population.begin(), population.end(), std::make_pair((double)randNum, -1));
		parent.second = itr->second;

		parents.push_back(parent);
	}

	return parents;
}

/// <summary>
/// Stochatic universal sampling
/// </summary>
/// <param name="population"></param>
/// <param name="parentSize"></param>
/// <returns></returns>
std::vector<std::pair<int, int>> selection::stochastic_universal_sampling(std::vector<std::pair<double, int>> population, int parentSize) {
	int amount = population.size();

	initPopulation(population);

	double totalPerc = 0;
	for (int i = 0; i < amount; i++) {
		population[i].first += totalPerc;
		totalPerc = population[i].first;
	}

	double pointDistance = population[amount - 1].first / parentSize / 2;

	std::vector<std::pair<int, int>> parents;

	std::pair<int, int> parent;
	std::vector<std::pair<double, int>>::iterator itr;
	double point;

	point = rand();

	while (parentSize--) {

		std::pair<int, int> parent;
		std::vector<std::pair<double, int>>::iterator itr;

		itr = std::lower_bound(population.begin(), population.end(), std::make_pair((double)point, -1));
		if (itr == population.end())break;
		parent.first = itr->second;

		itr = std::lower_bound(population.begin(), population.end(), std::make_pair((double)point + pointDistance, -1));
		if (itr == population.end())break;
		parent.second = itr->second;

		point += 2.0 * pointDistance;
		parents.push_back(parent);
	}
	return parents;
}
#pragma once
#include <vector>
#include "util.h"
#include <set>

class crossover
{
public:
	template <class T>
	static std::vector<T>  single_point_crossover(std::vector<T> parent1, std::vector<T> parent2);

	template <class T>
	static std::vector<T>  multi_point_crossover(std::vector<T> parent1, std::vector<T> parent2);

	template<class T>
	static std::vector<T>  uniform_crossover(std::vector<T> parent1, std::vector<T> parent2);
};

/// <summary>
/// a random crossover point is selected and the tails of its two parents are swapped to get new off-springs
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="parent1"></param>
/// <param name="parent2"></param>
/// <returns></returns>
template <class T>
std::vector<T>  crossover::single_point_crossover(std::vector<T> parent1, std::vector<T> parent2) {
	int point = util::rand(0, parent1.size() - 1);
	std::vector<T> offspring;
	for (int i = 0; i < point; i++)
		offspring.push_back(parent1[i]);
	for (int i = point; i < parent2.size(); i++)
		offspring.push_back(parent2[i]);
	return offspring;
}

/// <summary>
/// generalization of the one-point crossover wherein alternating segments are swapped to get new off-springs
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="parent1"></param>
/// <param name="parent2"></param>
/// <returns></returns>
template <class T>
std::vector<T>  crossover::multi_point_crossover(std::vector<T> parent1, std::vector<T> parent2) {
	int pointAmount = util::rand(1, parent1.size() / 2);
	std::set<int,std::greater<int>> points;
	for (int i = 0; i < pointAmount; i++)
		points.insert(util::rand(0, parent1.size() - 1));
	int x = 0;
	std::vector<T> offspring;
	for (int i = 0; i < parent1.size(); i++) {
		if (x)
			offspring.push_back(parent1[i]);
		else
			offspring.push_back(parent2[i]);
		if (points.count(i) != 0)
			x ^= 1;
	}
	return offspring;
}

/// <summary>
/// selecting chromosomes for each position of the child gene from parents with 50% probability for each
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="parent1"></param>
/// <param name="parent2"></param>
/// <returns></returns>
template<class T>
std::vector<T>  crossover::uniform_crossover(std::vector<T> parent1, std::vector<T> parent2) {
	std::vector<T> offspring;
	for (int i = 0; i < parent1.size(); i++)
		if (std::rand() % 100 < 50)
			offspring.push_back(parent1[i]);
		else
			offspring.push_back(parent2[i]);
	return offspring;
}



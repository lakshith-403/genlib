#pragma once

#include <iostream>
#include <vector>

class gencpp
{
public:
	template <class T>
	static std::vector<std::vector<T>> getNewGeneration(std::vector<std::vector<T>> population, double mutatationProbability, double (*fitnessFunction)(std::vector<T>), std::vector<T>(*mutationFunction)(std::vector<T>, double), std::vector<T>(*crossoverFunction)(std::vector<T>, std::vector<T>), std::vector<std::pair<int, int>>(*selectionFunction)(std::vector<std::pair<double, int>>, int));

	template <class T>
	static std::vector<T> getBest(std::vector<std::vector<T>> vec, double (*fitnessFunction)(std::vector<T>), std::vector<T> currentBest, double currentFitness);

	template <class T>
	static std::vector<T> evaluate(std::vector<std::vector<T>> initPopulation, int iterations, double mutationProbability, double (*fitnessFunction)(std::vector<T>), std::vector<T>(*mutationFunction)(std::vector<T>, double), std::vector<T>(*crossoverFunction)(std::vector<T>, std::vector<T>), std::vector<std::pair<int, int>>(*selectionFunction)(std::vector<std::pair<double, int>>, int));
};


template <class T>
std::vector<std::vector<T>> gencpp::getNewGeneration(std::vector<std::vector<T>> population, double mutatationProbability, double (*fitnessFunction)(std::vector<T>), std::vector<T>(*mutationFunction)(std::vector<T>, double), std::vector<T>(*crossoverFunction)(std::vector<T>, std::vector<T>), std::vector<std::pair<int, int>>(*selectionFunction)(std::vector<std::pair<double, int>>, int)) {
	std::vector<std::pair<double, int>> populationData;
	for (size_t i = 0; i < population.size(); i++)
		populationData.push_back(std::make_pair(fitnessFunction(population[i]), i));
	std::vector<std::pair<int, int>> parents = selectionFunction(populationData, populationData.size());
	std::vector<std::vector<T>> newGeneration;
	for (std::pair<int, int> parent : parents) {
		std::vector<T> child = crossoverFunction(population[parent.first], population[parent.second]);
		child = mutationFunction(child, mutatationProbability);
		newGeneration.push_back(child);
	}
	return newGeneration;
}

template <class T>
std::vector<T> gencpp::getBest(std::vector<std::vector<T>> vec, double (*fitnessFunction)(std::vector<T>), std::vector<T> currentBest, double currentFitness) {
	double fitness = currentFitness;
	std::vector<T> best = currentBest;
	for (std::vector<T> gene : vec)
		if (fitnessFunction(gene) > fitness) {
			fitness = fitnessFunction(gene);
			best = gene;
		}
	return best;
}

template <class T>
std::vector<T> gencpp::evaluate(std::vector<std::vector<T>> initPopulation, int iterations, double mutationProbability, double (*fitnessFunction)(std::vector<T>), std::vector<T>(*mutationFunction)(std::vector<T>, double), std::vector<T>(*crossoverFunction)(std::vector<T>, std::vector<T>), std::vector<std::pair<int, int>>(*selectionFunction)(std::vector<std::pair<double, int>>, int)) {
	std::vector<std::vector<T>> population = initPopulation;
	std::vector<T> best;
	double fitness = 0.0;
	for (int i = 0; i < iterations; i++) {
		population = getNewGeneration(population, mutationProbability, fitnessFunction, mutationFunction, crossoverFunction, selectionFunction);
		best = getBest(population, fitnessFunction, best, fitness);
		fitness = fitnessFunction(best);
		//std::cerr << fitness << "\n";
	}
	return best;
}

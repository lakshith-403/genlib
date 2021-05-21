#pragma once

#include <iostream>
#include <vector>
#include "util.h"

class gencpp
{
public:
	template <class T>
	static std::vector<std::vector<T>> getNewGeneration(std::vector<std::vector<T>> population, double mutatationProbability, double (*fitnessFunction)(std::vector<T>), std::vector<T>(*mutationFunction)(std::vector<T>, double), std::vector<T>(*crossoverFunction)(std::vector<T>, std::vector<T>), std::vector<std::pair<int, int>>(*selectionFunction)(std::vector<std::pair<double, int>>, int));

	template <class T>
	static std::vector<T> getBest(std::vector<std::vector<T>> vec, double (*fitnessFunction)(std::vector<T>), std::vector<T> currentBest, double currentFitness);

	template <class T>
	static std::pair<std::vector<T>, double> evaluate(std::vector<std::vector<T>> initPopulation, int iterations, double mutationProbability, double (*fitnessFunction)(std::vector<T>), std::vector<T>(*mutationFunction)(std::vector<T>, double), std::vector<T>(*crossoverFunction)(std::vector<T>, std::vector<T>), std::vector<std::pair<int, int>>(*selectionFunction)(std::vector<std::pair<double, int>>, int));
};

/// <summary>
/// Get a new generation of genes
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="population"></param>
/// <param name="mutatationProbability"></param>
/// <param name="fitnessFunction"></param>
/// <param name="mutationFunction"></param>
/// <param name="crossoverFunction"></param>
/// <param name="selectionFunction"></param>
/// <returns></returns>
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

/// <summary>
/// get the best gene out of the population
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="vec"></param>
/// <param name="fitnessFunction"></param>
/// <param name="currentBest"></param>
/// <param name="currentFitness"></param>
/// <returns></returns>
template <class T>
std::vector<T> gencpp::getBest(std::vector<std::vector<T>> population, double (*fitnessFunction)(std::vector<T>), std::vector<T> currentBest, double currentFitness) {
	double fitness = currentFitness;
	std::vector<T> best = currentBest;
	for (std::vector<T> gene : population)
		if (fitnessFunction(gene) > fitness) {
			fitness = fitnessFunction(gene);
			best = gene;
		}
	return best;
}

/// <summary>
/// Evaluate the genetic Algorithm and get the best gene and it's fitness
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="initPopulation"></param>
/// <param name="iterations"></param>
/// <param name="mutationProbability"></param>
/// <param name="fitnessFunction"></param>
/// <param name="mutationFunction"></param>
/// <param name="crossoverFunction"></param>
/// <param name="selectionFunction"></param>
/// <returns></returns>
template <class T>
std::pair<std::vector<T>,double> gencpp::evaluate(std::vector<std::vector<T>> initPopulation, int iterations, double mutationProbability, double (*fitnessFunction)(std::vector<T>), std::vector<T>(*mutationFunction)(std::vector<T>, double), std::vector<T>(*crossoverFunction)(std::vector<T>, std::vector<T>), std::vector<std::pair<int, int>>(*selectionFunction)(std::vector<std::pair<double, int>>, int)) {
	std::cout << "GenCPP Genetic Algorithm Library\n" << "Population size: " << initPopulation.size() << "\nNumber of generations: " << iterations << "\n";
	std::vector<std::vector<T>> population = initPopulation;
	std::vector<T> best;
	double fitness = 0.0;
	std::vector<double> graph;
	for (int i = 0; i < iterations; i++) {
		population = getNewGeneration(population, mutationProbability, fitnessFunction, mutationFunction, crossoverFunction, selectionFunction);
		best = getBest(population, fitnessFunction, best, fitness);
		fitness = fitnessFunction(best);
		std::cout << "\33[2K\rGeneration: " << i+1 << "\t" << "fitness: " << fitness << std::flush;
		graph.push_back(fitness);
	}
	std::cout << "\n\nBest Fitness: " << fitness << "\n";
	return std::make_pair(best,fitness);
}

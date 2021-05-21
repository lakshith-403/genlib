#pragma once
#include <vector>
#include <iostream>

class mutation
{
public:
	static bool check(double mutation_probability);

	template <typename T>
	static std::vector<T> swap_mutate(std::vector<T> gene, double mutation_probability);

	template <typename T>
	static std::vector<T> scramble_mutate(std::vector<T> gene, double mutation_probability);

	template <typename T>
	static std::vector<T> inverse_mutate(std::vector<T> gene, double mutation_probability);
};

#include "util.h"


bool mutation::check(double mutation_probability) {
	return (std::rand() % 101) < (int)(mutation_probability * 100.0);
}

/// <summary>
/// Swap choromosomes in randomly selected pairs of positions
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="gene"></param>
/// <param name="mutation_probability"></param>
/// <returns></returns>
template <typename T>
std::vector<T> mutation::swap_mutate(std::vector<T> gene, double mutation_probability) {
	int swapCount = (int)(mutation_probability * 100.0);
	while (swapCount--) {
		// if (!check())continue;
		int a = util::rand(0, gene.size() - 1), b = util::rand(0, gene.size() - 1);
		T tempChrom = gene[a];
		gene[a] = gene[b];
		gene[b] = tempChrom;
	}
	return gene;
}

/// <summary>
/// Randomly shuffle the positions of the chromosomes  in a subset of the gene
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="gene"></param>
/// <param name="mutation_probability"></param>
/// <returns></returns>
template <typename T>
std::vector<T> mutation::scramble_mutate(std::vector<T> gene, double mutation_probability) {
	int l = util::rand(0, gene.size() - 1), r = util::rand(l, gene.size() - 1);
	for (int i = l; i <= r; i++) {
		if (!check(mutation_probability))continue;
		int j = util::rand(l, r);
		T tempChrom = gene[i];
		gene[i] = gene[j];
		gene[j] = tempChrom;
	}
	return gene;
}

/// <summary>
/// Inverse the positions of choromosomes in the genes
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="gene"></param>
/// <param name="mutation_probability"></param>
/// <returns></returns>
template <typename T>
std::vector<T> mutation::inverse_mutate(std::vector<T> gene, double mutation_probability) {
	int l = util::rand(0, gene.size() - 1), r = util::rand(l, gene.size() - 1);
	std::cerr << l << " " << r << "\n";
	for (int i = l; i <= l + (r - l) / 2; i++) {
		if (!check(mutation_probability))continue;
		int j = r - i;
		T tempChrom = gene[i];
		gene[i] = gene[j];
		gene[j] = tempChrom;
	}
	return gene;
}

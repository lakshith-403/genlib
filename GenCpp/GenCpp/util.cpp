#include "util.h"
#include <vector>
#include <iostream>

/// <summary>
/// Returns an integer between the given range
/// </summary>
/// <param name="l">lower bound of integers</param>
/// <param name="r">upper bound of integers</param>
/// <returns></returns>
int util::rand(int l, int r) {
	return l + std::rand() % (r - l + 1);
}

/// <summary>
/// Returns a vector of genses with char chromosomes
/// </summary>
/// <param name="geneLength">No of choromosomes in a single gene</param>
/// <param name="gense">No of genes</param>
/// <returns></returns>
std::vector<std::vector<char>> util::generateCharGenes(int geneLength, int genes) {
	std::vector<std::vector<char>> vec;
	while (genes--) {
		std::vector<char> s;
		for (int j = 0; j < geneLength; j++)
			s.push_back((char)('a' + std::rand() % 26));
		vec.push_back(s);
	}
	return vec;
}

/// <summary>
/// Reterns a vector of genes with int chromosomes
/// </summary>
/// <param name="geneLength">No of choromosomes in a single gene</param>
/// <param name="gense">No of genes</param>
/// <param name="l">Lower bound of integers</param>
/// <param name="r">Upper bound of integers</param>
/// <returns></returns>
std::vector<std::vector<int>> util::generateIntGenes(int geneLength, int genes, int l, int r) {
	std::vector<std::vector<int>> vec;
	while (genes--) {
		std::vector<int> v;
		for (int i = 0; i < geneLength; i++)
			v.push_back(util::rand(l, r));
		vec.push_back(v);
	}
	return vec;
}
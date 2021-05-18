#pragma once

#include <vector>

class util
{
public:

	int rand(int l, int r);

	std::vector<std::vector<char>> generateCharGenes(int geneLength, int genes);

	std::vector<std::vector<int>> generateIntGenes(int geneLength, int genes, int l, int r);
};


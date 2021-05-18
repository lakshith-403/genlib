#pragma once

#include <vector>

class util
{
public:

	static int rand(int l, int r);

	static std::vector<std::vector<char>> generateCharGenes(int geneLength, int genes);

	static std::vector<std::vector<int>> generateIntGenes(int geneLength, int genes, int l, int r);
};


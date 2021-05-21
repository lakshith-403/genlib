#include "gencpp.h"
#include "util.h"
#include "mutation.h"
#include "selection.h"
#include "crossover.h"
#include <vector>
#include <iostream>

using namespace std;

double f(vector<char> a) {
	double r = 0;
	string t = "lakshith";
	for (int i = 0; i < (int)a.size(); i++) r += (double)(t[i] == a[i]);
	return r;
}

int main() {
	vector<vector<char>> initPop = util::generateCharGenes(8,100);
	pair<vector<char>, double> best = gencpp::evaluate<char>(initPop, 100, 0.1, f,
			mutation::scramble_mutate, crossover::uniform_crossover, selection::roulette_wheel_selection);
	cout << best.second << "\n";
	for (char a : best.first)cout << a;
}
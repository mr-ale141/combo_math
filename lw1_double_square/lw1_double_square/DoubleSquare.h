#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

unsigned int GetMinR(
	const int N,
	const std::vector<std::vector<int>>& const cargoMatrix,
	const std::vector<std::vector<int>>& const locationMatrix,
	std::vector<int>& companyesMin,
	std::vector<int>& locationsMin
);
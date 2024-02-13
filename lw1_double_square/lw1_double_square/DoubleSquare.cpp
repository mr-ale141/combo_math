#include "DoubleSquare.h"

size_t GetMinR(
	const int N,
	const std::vector<std::vector<int>>& const cargoMatrix,
	const std::vector<std::vector<int>>& const locationMatrix,
	std::vector<int>& companyesMin,
	std::vector<int>& locationsMin
)
{
	std::vector<int> companyes;
	for (int i = 0; i < N; i++)	companyes.push_back(i);
	std::vector<int> locations;
	for (int i = 0; i < N; i++)	locations.push_back(i);
	size_t minR = UINT_MAX;

	do
	{
		do
		{
			size_t R = 0;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					int companyCurrent = companyes[i];
					int companyRelation = companyes[j];
					if (companyCurrent == companyRelation) continue;
					int locationCurrent = locations[i];
					int locationRelation = locations[j];
					int cargo = cargoMatrix[companyCurrent][companyRelation];
					int dist = locationMatrix[locationCurrent][locationRelation];
					int currR = dist * cargo;
					R += currR;
				}
			}
			if (R < minR)
			{
				minR = R;
				companyesMin = companyes;
				locationsMin = locations;
			}
			/*
			std::cout << "Company : ";
			for (auto i : companyes)
			std::cout << i + 1 << ' ';
			std::cout << std::endl;
			std::cout << "Location: ";
			for (auto i : locations)
			std::cout << i + 1 << ' ';
			std::cout << std::endl;
			std::cout << "Cur R = " << R << std::endl;
			*/
		} while (std::next_permutation(locations.begin(), locations.end()));
	} while (std::next_permutation(companyes.begin(), companyes.end()));

	return minR;
}
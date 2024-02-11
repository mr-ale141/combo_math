#include <iostream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../lw1_double_square/DoubleSquare.h"

TEST_CASE("Test 2 x 2")
{
	int N = 2;
	std::vector<std::vector<int>> cargoMatrix
	{
		{ 0, 5 },
		{ 2, 0 }
	};
	std::vector<std::vector<int>> locationMatrix
	{
		{ 0, 3 },
		{ 3, 0 }
	};
	std::vector<int> companyesMin;
	std::vector<int> locationsMin;
	auto minR = GetMinR(N, cargoMatrix, locationMatrix, companyesMin, locationsMin);
	
	std::cout << "Min R = " << minR << std::endl;

	std::cout << "CompanyMin : ";
	for (auto i : companyesMin)
		std::cout << i + 1 << ' ';
	std::cout << std::endl;

	std::cout << "LocationMin: ";
	for (auto i : locationsMin)
		std::cout << i + 1 << ' ';
	std::cout << std::endl;

	REQUIRE(companyesMin[0] + 1 == 1);
	REQUIRE(companyesMin[1] + 1 == 2);

	REQUIRE(locationsMin[0] + 1 == 1);
	REQUIRE(locationsMin[1] + 1 == 2);
	
	REQUIRE(minR == 21);
}

TEST_CASE("Test 3 x 3")
{
	int N = 3;
	std::vector<std::vector<int>> cargoMatrix
	{
		{  0, 15, 20 },
		{ 16,  0,  7 },
		{  2, 10,  0 }
	};
	std::vector<std::vector<int>> locationMatrix
	{
		{  0,  8, 10 },
		{ 15,  0,  6 },
		{  2,  5,  0 }
	};
	std::vector<int> companyesMin;
	std::vector<int> locationsMin;
	auto minR = GetMinR(N, cargoMatrix, locationMatrix, companyesMin, locationsMin);

	std::cout << "Min R = " << minR << std::endl;

	std::cout << "CompanyMin : ";
	for (auto i : companyesMin)
		std::cout << i + 1 << ' ';
	std::cout << std::endl;

	std::cout << "LocationMin: ";
	for (auto i : locationsMin)
		std::cout << i + 1 << ' ';
	std::cout << std::endl;

	REQUIRE(companyesMin[0] + 1 == 1);
	REQUIRE(companyesMin[1] + 1 == 2);
	REQUIRE(companyesMin[2] + 1 == 3);

	REQUIRE(locationsMin[0] + 1 == 3);
	REQUIRE(locationsMin[1] + 1 == 2);
	REQUIRE(locationsMin[2] + 1 == 1);

	REQUIRE(minR == 416);
}

TEST_CASE("Test 4 x 4")
{
	int N = 4;
	std::vector<std::vector<int>> cargoMatrix
	{
		{  0, 11, 12, 13 },
		{ 21,  0, 14, 15 },
		{ 22, 23,  0, 16 },
		{ 24, 25, 26,  0 }
	};
	std::vector<std::vector<int>> locationMatrix
	{
		{  0, 14, 15, 16 },
		{ 26,  0, 12, 13 },
		{ 25, 24,  0, 11 },
		{ 23, 22, 21,  0 }
	};
	std::vector<int> companyesMin;
	std::vector<int> locationsMin;
	auto minR = GetMinR(N, cargoMatrix, locationMatrix, companyesMin, locationsMin);

	std::cout << "Min R = " << minR << std::endl;

	std::cout << "CompanyMin : ";
	for (auto i : companyesMin)
		std::cout << i + 1 << ' ';
	std::cout << std::endl;

	std::cout << "LocationMin: ";
	for (auto i : locationsMin)
		std::cout << i + 1 << ' ';
	std::cout << std::endl;

	REQUIRE(companyesMin[0] + 1 == 1);
	REQUIRE(companyesMin[1] + 1 == 2);
	REQUIRE(companyesMin[2] + 1 == 3);
	REQUIRE(companyesMin[3] + 1 == 4);

	REQUIRE(locationsMin[0] + 1 == 4);
	REQUIRE(locationsMin[1] + 1 == 3);
	REQUIRE(locationsMin[2] + 1 == 2);
	REQUIRE(locationsMin[3] + 1 == 1);

	REQUIRE(minR == 3837);
}

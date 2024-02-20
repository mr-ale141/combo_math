#define CATCH_CONFIG_MAIN
#include "../lw2_backpack/PutInBackpack.h"
#include "../../Catch2/catch.hpp"
#include <chrono>


TEST_CASE("Test N = 0")
{
	std::cout << "--------- Test N = 0 --------" << std::endl;
	int maxWeight = 250;
	std::vector<int> prices{};
	std::vector<int> weights{};
	std::vector<int> backpack;
	
	std::cout << "Prices  : ";
	PrintVector(prices);

	std::cout << "Weights : ";
	PrintVector(weights);

	PutInBackpack(backpack, prices, weights, maxWeight);

	std::cout << "Backpack: ";
	PrintVector(backpack);

	REQUIRE(backpack.size() == 0);
	std::cout << "----------- Finish ----------" << std::endl;
}

TEST_CASE("Test N = 1")
{
	std::cout << "--------- Test N = 1 --------" << std::endl;
	int maxWeight = 250;
	std::vector<int> prices{20};
	std::vector<int> weights{250};
	std::vector<int> backpack;

	std::cout << "Prices  : ";
	PrintVector(prices);

	std::cout << "Weights : ";
	PrintVector(weights);

	PutInBackpack(backpack, prices, weights, maxWeight);

	std::cout << "Backpack: ";
	PrintVector(backpack);

	REQUIRE(backpack[0] == 1);
	std::cout << "----------- Finish ----------" << std::endl;
}

TEST_CASE("Test N = 1 empty")
{
	std::cout << "--------- Test N = 1 empty---" << std::endl;
	int maxWeight = 250;
	std::vector<int> prices{ 20 };
	std::vector<int> weights{ 251 };
	std::vector<int> backpack;

	std::cout << "Prices  : ";
	PrintVector(prices);

	std::cout << "Weights : ";
	PrintVector(weights);

	PutInBackpack(backpack, prices, weights, maxWeight);

	std::cout << "Backpack: ";
	PrintVector(backpack);

	REQUIRE(backpack.size() == 0);
	std::cout << "----------- Finish ----------" << std::endl;
}

TEST_CASE("Test N = 2")
{
	std::cout << "--------- Test N = 2 --------" << std::endl;
	int maxWeight = 250;
	std::vector<int> prices{ 20, 0 };
	std::vector<int> weights{ 250, 100 };
	std::vector<int> backpack;

	std::cout << "Prices  : ";
	PrintVector(prices);

	std::cout << "Weights : ";
	PrintVector(weights);

	PutInBackpack(backpack, prices, weights, maxWeight);

	std::cout << "Backpack: ";
	PrintVector(backpack);

	REQUIRE(backpack[0] == 1);
	std::cout << "----------- Finish ----------" << std::endl;
}

TEST_CASE("Test N = 2 Empty")
{
	std::cout << "--------- Test N = 2 Empty---" << std::endl;
	int maxWeight = 250;
	std::vector<int> prices{ 20, 30 };
	std::vector<int> weights{ 251, 500 };
	std::vector<int> backpack;

	std::cout << "Prices  : ";
	PrintVector(prices);

	std::cout << "Weights : ";
	PrintVector(weights);

	PutInBackpack(backpack, prices, weights, maxWeight);

	std::cout << "Backpack: ";
	PrintVector(backpack);

	REQUIRE(backpack.size() == 0);
	std::cout << "----------- Finish ----------" << std::endl;
}

TEST_CASE("Test N = 10")
{
	std::cout << "--------- Test N = 10 -------" << std::endl;
	int maxWeight = 250;
	std::vector<int> prices{ 10,  5, 20, 100,   1, 30,  9, 14, 50, 47 };
	std::vector<int> weights{  1, 50, 15,  90, 100, 50, 18, 69, 48, 90 };
	std::vector<int> backpack;

	std::cout << "Prices  : ";
	PrintVector(prices);

	std::cout << "Weights : ";
	PrintVector(weights);

	PutInBackpack(backpack, prices, weights, maxWeight);

	std::cout << "Backpack: ";
	PrintVector(backpack);

	REQUIRE(backpack[0] == 1);
	REQUIRE(backpack[1] == 3);
	REQUIRE(backpack[2] == 4);
	REQUIRE(backpack[3] == 9);
	REQUIRE(backpack[4] == 10);
	std::cout << "----------- Finish ----------" << std::endl;
}


TEST_CASE("Test N = 10 all")
{
	std::cout << "--------- Test N = 10 all -------" << std::endl;
	
	int maxWeight = 9;
	std::vector<int> prices{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> weights{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	std::vector<int> backpack;

	std::cout << "Prices  : ";
	PrintVector(prices);

	std::cout << "Weights : ";
	PrintVector(weights);

	auto timeBegin = std::chrono::high_resolution_clock::now();
	PutInBackpack(backpack, prices, weights, maxWeight);
	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin);
	std::cout << "Delta Time = " << us.count() << " us" << std::endl;

	std::cout << "Backpack: ";
	PrintVector(backpack);

	REQUIRE(backpack[0] == 2);
	REQUIRE(backpack[1] == 3);
	REQUIRE(backpack[2] == 4);
	REQUIRE(backpack[3] == 5);
	REQUIRE(backpack[4] == 6);
	REQUIRE(backpack[5] == 7);
	REQUIRE(backpack[6] == 8);
	REQUIRE(backpack[7] == 9);
	REQUIRE(backpack[8] == 10);
	std::cout << "----------- Finish ----------" << std::endl;
}


TEST_CASE("Test N = 10 one")
{
	std::cout << "--------- Test N = 10 one -------" << std::endl;

	int maxWeight = 1;
	std::vector<int> prices{ 250, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> weights{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	std::vector<int> backpack;

	std::cout << "Prices  : ";
	PrintVector(prices);

	std::cout << "Weights : ";
	PrintVector(weights);

	auto timeBegin = std::chrono::high_resolution_clock::now();
	PutInBackpack(backpack, prices, weights, maxWeight);
	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin);
	std::cout << "Delta Time = " << us.count() << " us" << std::endl;

	std::cout << "Backpack: ";
	PrintVector(backpack);

	REQUIRE(backpack[0] == 1);
	std::cout << "----------- Finish ----------" << std::endl;
}
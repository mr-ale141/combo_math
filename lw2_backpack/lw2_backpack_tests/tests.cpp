#define CATCH_CONFIG_MAIN
#include "../lw2_backpack/PutInBackpack.h"
#include "../../Catch2/catch.hpp"


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
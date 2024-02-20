/*
	Задача об укладке рюкзака.
	
	Есть 𝑛 различных предметов. Каждый предмет с номером 𝑖,
	где  𝑖=1,…,𝑛,  имеет  заданный  положительный вес 𝑤_𝑖 и
	стоимость 𝑐_𝑖. Нужно  уложить рюкзак  так, чтобы  общая
	стоимость предметов  в  нём  была  наибольшей, а вес не
	превышал заданного 𝑇. Форма предметов значения не имеет.
	
	Сдача работы без тестов – коэффициент 0.5.
*/

#include "PutInBackpack.h"

int main(int argc, char* argv)
{
	int maxWeight = 250;
	std::vector<int> prices{ 10,  5, 20, 100,   1, 30,  9, 14, 50, 47 };
	// std::vector<int> prices{50};
	std::vector<int> weights{ 1, 50, 15,  90, 100, 50, 18, 69, 48, 90 };
	// std::vector<int> weights{251};
	std::vector<int> backpack;

	PutInBackpack(backpack, prices, weights, maxWeight);

	PrintVector(backpack);
	// Answer: 1, 3, 4, 9, 10
}
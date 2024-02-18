/*
	start: (1, 2, 3, ..., k)
	end  : (𝑛−𝑘+1, 𝑛−𝑘+2, …, 𝑛−1, 𝑛)
*/

#include "PutInBackpack.h"

bool GetNextSet(std::vector<int>& backpack, int n)
{
	int k = backpack.size();
	for (int i = k - 1; i >= 0; i--)
	{
		if (backpack[i] < n - k + i + 1)
		{
			++backpack[i];
			for (int j = i + 1; j < k; ++j)
				backpack[j] = backpack[j - 1] + 1;
			return true;
		}
	}
	return false;
}

int GetSummParameters(std::vector<int>& backpack,
	                  std::vector<int>& parameters)
{
	int currentWeight = 0;
	int size = backpack.size();
	for (int i = 0; i < size; i++)
		currentWeight += parameters[backpack[i] - 1];
	return currentWeight;
}

void PrintVector(std::vector<int>& backpack)
{
	for (auto item : backpack)
	{
		std::cout.width(3);
		std::cout << item << '|';
	}
	std::cout << std::endl;
}

void PutInBackpack(std::vector<int>& backpack, 
	               std::vector<int>& prices, 
                   std::vector<int>& weights, 
	               int maxWeight)
{
	int n = prices.size();

	// Создаем временный рюкзак
	std::vector<int> holdBackpack;

	// Сначала кладем все объекты во временный рюкзак
	for (int i = 0; i < n; i++)
		holdBackpack.push_back(i + 1);

	// Измеряем вес во временном рюкзаке со всеми предметами
	int holdWeight = GetSummParameters(holdBackpack, weights);

	// Если можем забрать все объекты, то забираем
	if (holdWeight <= maxWeight)
	{
		backpack = holdBackpack;
		return;
	}

	// Цена во временном рюкзаке
	int holdPrice;

	// Текущая стоимость в основном рюкзаке
	int currentPrice = 0;

	while (holdBackpack.size())
	{
		// Проверяем содержимое временного рюкзака на ограничение по весу и цене с основным
		holdWeight = GetSummParameters(holdBackpack, weights);
		holdPrice = GetSummParameters(holdBackpack, prices);
		if (holdWeight <= maxWeight && holdPrice > currentPrice)
		{
			// Сохраняем более лучшую комбинацию предметов
			currentPrice = holdPrice;
			backpack = holdBackpack;
		}

		// Берем следующую комбинацию подмножества
		if (!GetNextSet(holdBackpack, n))
		{
			// Если комбинации закончились, то уменьшаем размер подмножества для поиска
			holdBackpack.pop_back();
			for (int i = 0; i < holdBackpack.size(); i++)
				holdBackpack[i] = i + 1;
		}
	}
}

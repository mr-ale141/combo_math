#pragma once
#include <iostream>
#include <vector>

void PutInBackpack(std::vector<int>& backpack,
				   std::vector<int>& prices,
				   std::vector<int>& weights,
				   int maxWeight);

void PrintVector(std::vector<int>& backpack);
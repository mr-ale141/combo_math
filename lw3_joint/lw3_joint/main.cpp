#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 50;

std::vector<int> graph[MAXN];
bool used[MAXN];
int timer;
int tin[MAXN];
int fup[MAXN]; // min (tin[current], tin[parent], fup[to])

void PrintArticulationPoint(int point)
{
	std::cout << "Articulation Point = " << point << std::endl;
}

//current - Articulation Point if:
//fup[to] >= tin[current] 

//used[to] == false                   - dfs first
//used[to] == true && to != parrent   - back path
//to == parrent                       - back loop

void FindArticulationPoint(int current, int parent = -1)
{
	used[current] = true;
	tin[current] = fup[current] = timer++;
	int children = 0;
	for (size_t i = 0; i < graph[current].size(); ++i)
	{
		int to = graph[current][i];
		if (to == parent)
		{
			continue;
		}
		if (used[to])
		{
			fup[current] = std::min(fup[current], tin[to]);
		}
		else
		{
			FindArticulationPoint(to, current);
			fup[current] = std::min(fup[current], fup[to]);
			if (fup[to] >= tin[current] && parent != -1)
			{
				PrintArticulationPoint(current);
			}
			++children;
		}
	}
	if (parent == -1 && children > 1)
	{
		PrintArticulationPoint(current);
	}
}

/*

1 - 2
|   |
0 - 3
 \ /
  4
 / \
5 - 7
 \ /
  6

  int n = 8;
  g[0] = {2, 4, 5};
  g[1] = {0, 2};
  g[2] = {1, 3};
  g[3] = {0, 2, 4};
  g[4] = {0, 3, 5, 7};
  g[5] = {4, 6, 7};
  g[6] = {5, 7};
  g[7] = {4, 5, 6};

*/

/*
       0   10
      / \ /
 9   6   1   4   5
  \ / \   \ / \ / 
   8 - 7   2 - 3

int n = 11;
g[0] = {6,1};
g[1] = {0,2,10};
g[2] = {1,3,4};
g[3] = {2,4,5};
g[4] = {2,3};
g[5] = {3};
g[6] = {0,7,8};
g[7] = {6,8};
g[8] = {6,7,9};
g[9] = {8};
g[10] = {1};
*/

/*

0 - 1
 \ /
  2
 / \
3 - 4

int n = 5;
g[0] = {1,2};
g[1] = {0,2};
g[2] = {0,1,3,4};
g[3] = {2,4};
g[4] = {2,3};
*/

int main() {
	int n = 5;
	graph[0] = { 1,2 };
	graph[1] = { 0,2 };
	graph[2] = { 0,1,3,4 };
	graph[3] = { 2,4 };
	graph[4] = { 2,3 };

	timer = 0;
	for (int i = 0; i < n; ++i)
	{
		used[i] = false;
	}
	FindArticulationPoint(0);
}
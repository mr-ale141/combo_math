#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 50;

std::vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];

void PrintJoint(int v)
{
	std::cout << "Joint = " << v << std::endl;
}

//used[to] == false                   - dfs first
//used[to] == true && to != parrent   - back path
//to == parrent                       - back loop

void FindJoint(int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p) 
			continue;
		if (used[to])
			fup[v] = std::min(fup[v], tin[to]);
		else {
			FindJoint(to, v);
			fup[v] = std::min(fup[v], fup[to]);
			if (fup[to] >= tin[v] && p != -1)
				PrintJoint(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		PrintJoint(v);
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
	g[0] = { 1,2 };
	g[1] = { 0,2 };
	g[2] = { 0,1,3,4 };
	g[3] = { 2,4 };
	g[4] = { 2,3 };

	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	FindJoint(0);
}
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 2001;
int n;
char code[NN][8];
int mat[NN][NN];
int lowcost[NN];

int prim(int s)
{
	for (int i = 0; i < n; ++i) {
		lowcost[i] = mat[s][i];
	}
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int minCost = INT_MAX;
		int u = -1;
		for (int j = 0; j < n; ++j) {
			if (lowcost[j] != -1 && minCost > lowcost[j]) {
				minCost = lowcost[j];
				u = j;
			}
		}
		if (u == -1) return -1;
		sum += minCost;
		lowcost[u] = -1;
		for (int j = 0; j < n; ++j) {
			if (lowcost[j] != -1 && lowcost[j] > mat[u][j]) {
				lowcost[j] = mat[u][j];
			}
		}
	}
	return sum;
}

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) {
			scanf("%s", code[i]);
			for (int j = 0; j < i; ++j) {
				int d = 0;
				for (int k = 0; k < 7; ++k) {
					if (code[i][k] != code[j][k]) {
						++d;
					}
				}
				mat[i][j] = mat[j][i] = d;
			}
			mat[i][i] = 0;
		}
		printf("The highest possible quality is 1/%d.\n", prim(0));
	}
	return 0;
}


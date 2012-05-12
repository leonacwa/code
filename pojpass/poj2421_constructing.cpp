#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 101;
int n;
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
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &mat[i][j]);
			}
		}
		int q;
		scanf("%d", &q);
		for (int i = 0; i < q; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			--u, --v;
			mat[u][v] = mat[v][u] = 0;
		}
		printf("%d\n", prim(0));
	}
	return 0;
}


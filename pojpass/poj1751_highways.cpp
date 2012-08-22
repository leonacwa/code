#include <cstdio>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <iostream>
using namespace std;
const int NN = 755;
struct Town {
	int x, y;
};
int n;
Town tn[NN];
double mat[NN][NN];
double lowcost[NN];
int pvex[NN];

void prim(int s)
{
	for (int i = 1; i <= n; ++i) {
		lowcost[i] = mat[s][i];
		pvex[i] = s;
	}
	pvex[s] = -1;
	lowcost[s] = -DBL_MAX;
	for (int i = 1; i < n; ++i) {
		double minCost = DBL_MAX;
		int u = -1;
		for (int j = 1; j <= n; ++j) {
			if (lowcost[j] > -1 && minCost > lowcost[j]) {
				minCost = lowcost[j];
				u = j;
			}
		}
		if (u == -1) {
			return;
		}
		lowcost[u] = -DBL_MAX;
		if (minCost > 0.0) {
			int a = pvex[u], b = u;
			if (a > b) swap(a, b);
			printf("%d %d\n", a, b);
		}
		for (int j = 1; j <= n; ++j) {
			if (lowcost[j] > -1 && lowcost[j] > mat[u][j]) {
				lowcost[j] = mat[u][j];
				pvex[j] = u;
			}
		}
	}
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d\n", &n) && n > 0) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d\n", &tn[i].x, &tn[i].y);
			for (int j = 1; j < i; ++j) {
				double x = tn[i].x - tn[j].x, y = tn[i].y - tn[j].y;
				mat[i][j] = mat[j][i] = sqrt(x * x + y * y);
				
			}
			mat[i][i] = 0.0;
		}
		int m = 0;
		scanf("%d\n", &m);
		for (int i = 0; i < m; ++i) {
			int u = 0, v = 0;
			scanf("%d %d\n", &u, &v);
			mat[u][v] = mat[v][u] = 0.0;
		}
		if (nCase++) puts("");
		prim(1);
		break;
	}
	return 0;
}


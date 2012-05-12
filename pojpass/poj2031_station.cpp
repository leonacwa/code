#include <cstdio>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 101;
struct Sphere {
	double x, y, z, r;
};
int n;
Sphere sp[NN];
double mat[NN][NN];
double lowcost[NN];

double prim(int s)
{
	for (int i = 0; i < n; ++i) {
		lowcost[i] = mat[s][i];
	}
	double sum = 0.0;
	for (int i = 0; i < n; ++i) {
		double minCost = DBL_MAX;
		int u = -1;
		for (int j = 0; j < n; ++j) {
			if (lowcost[j] > -1 && minCost > lowcost[j]) {
				minCost = lowcost[j];
				u = j;
			}
		}
		if (u == -1) return -DBL_MAX;
		sum += minCost;
		lowcost[u] = -DBL_MAX;
		for (int j = 0; j < n; ++j) {
			if (lowcost[j] > -1 && lowcost[j] > mat[u][j]) {
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
			scanf("%lf %lf %lf %lf", &sp[i].x, &sp[i].y, &sp[i].z, &sp[i].r);
			for (int j = 0; j < i; ++j) {
				double x = sp[i].x - sp[j].x, y = sp[i].y - sp[j].y, z = sp[i].z - sp[j].z;
				double d = sqrt(x * x + y * y + z * z) - sp[i].r - sp[j].r;
				if (d < 0) {
					d = 0.0;
				}
				mat[i][j] = mat[j][i] = d;
			}
			mat[i][i] = 0.0;
		}
		printf("%.3f\n", prim(0));
	}
	return 0;
}


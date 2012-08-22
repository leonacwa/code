#include <cstdio>
#include <cstring>
#include <cfloat>
#include <cmath>
#include <iostream>
using namespace std;
const int NN = 21;
const int MP = NN * 4 + 2;
struct Edge {
	int u, v;
	double w;
} E[MP * MP];
int n, nE, pCnt;
double wX[NN], wY[NN][4];
double pX[MP], pY[MP];
double len[MP];

double cross(double x2, double y2, double x1, double y1, double x0, double y0)
{
	return (x2 - x0) * (y1 - y0) - (x1 - x0) * (y2 - y0);
}

bool isOk(double x1, double y1, double x2, double y2)
{
	int i = 0;
	while (wX[i] <= x1 && i < n) {
		++i;
	}
	for (; i < n && wX[i] < x2; ++i) {
		if (cross(wX[i], 0, x2, y2, x1, y1) * cross(wX[i], wY[i][0], x2, y2, x1, y1) < 0) return false;
		if (cross(wX[i], wY[i][1], x2, y2, x1, y1) * cross(wX[i], wY[i][2], x2, y2, x1, y1) < 0) return false;
		if (cross(wX[i], wY[i][3], x2, y2, x1, y1) * cross(wX[i], 10, x2, y2, x1, y1) < 0) return false;
	}
	return true;
}

double dis(double x1, double y1, double x2, double y2)
{
	double dx = x1 - x2, dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}

double bellman_ford(int begin, int end)
{
	for (int i = 0; i < pCnt; ++i) {
		len[i] = DBL_MAX;
	}
	len[begin] = 0;
	bool change = true;
	for (int i = 0; i < pCnt && change; ++i) {
		change = false;
		for (int j = 0; j < nE; ++j) {
			int u = E[j].u, v = E[j].v;
			double w = E[j].w;
			if (len[u] < DBL_MAX && (len[v] > len[u] + w)) {
				len[v] = len[u] + w;
				change = true;
			}
			if (len[v] < DBL_MAX && (len[u] > len[v] + w)) {
				len[u] = len[v] + w;
				change = true;
			}
		}
	}
	return len[end];
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		if (n == -1) break;
		pCnt = 1;
		pX[0] = 0;
		pY[0] = 5;
		for (int i = 0; i < n; ++i) {
			scanf("%lf", &wX[i]);
			for (int j = 0; j < 4; ++j) {
				scanf("%lf", &wY[i][j]);
				pX[pCnt] = wX[i];
				pY[pCnt] = wY[i][j];
				++pCnt;
			}
		}
		pX[pCnt] = 10;
		pY[pCnt] = 5;
		++pCnt;
		nE = 0;
		for (int i = 0; i < pCnt; ++i) {
			for (int j = i + 1; j < pCnt; ++j) {
				if (isOk(pX[i], pY[i], pX[j], pY[j])) {
					E[nE].u = i;
					E[nE].v = j;
					E[nE].w = dis(pX[i], pY[i], pX[j], pY[j]);
					++nE;
				}
			}
		}
		double ans = bellman_ford(0, pCnt - 1);
		printf("%.2f\n", ans);
	}
	return 0;
}


#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <cfloat>
#include <iostream>
using namespace std;
const int NN = 101;
struct Point {
	int x, y;
};
int n;
Point spot[NN][NN];
int cnt[NN];
double f[NN][NN];

double getDis(const Point &a, const Point &b)
{
	double x = a.x - b.x, y = a.y - b.y;
	return sqrt(x *x + y * y);
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", cnt + i);
			for (int j = 0; j < cnt[i]; ++j) {
				scanf("%d %d", &spot[i][j].x, &spot[i][j].y);
			}
		}
		double ans = DBL_MAX;
		for (int a = 0; a < cnt[0]; ++a) {
			for (int i = 0; i < cnt[1]; ++i) {
				f[1][i] = getDis(spot[0][a], spot[1][i]);
			}
			for (int i = 2; i < n; ++i) {
				for (int j = 0; j < cnt[i]; ++j) {
					f[i][j] = DBL_MAX;
					for (int k = 0; k < cnt[i-1]; ++k) {
						f[i][j] = min(f[i][j], f[i-1][k] + getDis(spot[i-1][k], spot[i][j]));
					}
				}
			}
			f[0][a] = DBL_MAX;
			for (int i = 0; i < cnt[n-1]; ++i) {
				f[0][a] = min(f[0][a], f[n-1][i] + getDis(spot[n-1][i], spot[0][a]));
			}
			if (ans > f[0][a]) ans = f[0][a];
		}
		printf("%d\n", (int)(ans * 100 + 1e-6)); // 会有一定误差，有时需要加上1e-6去调整误差
	}
	return 0;
}


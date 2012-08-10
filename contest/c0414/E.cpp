#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 202;
typedef long long LLONG;
struct Point {
	LLONG x, y;
};
int cnt[NN][NN];
Point loli[NN], uncle[NN];

bool cmpx(const Point &a, const Point &b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

LLONG mult(const Point &p2, const Point &p1, const Point &p0) {
	return (p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y);
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf("%lld %lld", &loli[i].x, &loli[i].y);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%lld %lld", &uncle[i].x, &uncle[i].y);
		}
		sort(loli, loli + n, cmpx);
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				for (int k = 0; k < m; ++k) {
					if (loli[i].x <= uncle[k].x && uncle[k].x < loli[j].x) {
						if (mult(uncle[k], loli[j], loli[i]) < 0) {
							cnt[i][j]++;
						}
					}
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				for (int k = j+1; k < n; ++k) {
					if (cnt[i][j] + cnt[j][k] == cnt[i][k]) {
						++ans;
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


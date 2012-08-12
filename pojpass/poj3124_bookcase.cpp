/* The Bookcase
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 0x3fffffff;

int f[2101][2101];

struct Book {
	int h, t;
} b[105];

bool cmph(const Book &A, const Book &B) {
	return A.h > B.h;
}

int main() {
	int runs, n;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d", &n);
		int tsum = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &b[i].h, &b[i].t);
			tsum += b[i].t;
		}
		sort(b, b + n, cmph);
		for (int i = 0; i <= tsum - b[0].t; ++i) {
			for (int j = 0; j <= tsum - b[0].t; ++j) {
				f[i][j] = INF;
			}
		}
		f[0][0] = 0;
		int tmax = 0;
		for (int i = 1; i < n; ++i) {
			int h = b[i].h, t = b[i].t;
			for (int j = tmax; j >= 0; --j) {
				for (int k = tmax; k >= 0; --k) {
					if (f[j][k] >= INF) continue;
					if (j >  0) {
						if (f[j+t][k] > f[j][k]) f[j+t][k] = f[j][k];
					} else {
						if (f[t][k] > f[0][k]) f[t][k] = f[0][k] + h;
					}
					if (k >  0) {
					   if (f[j][k+t] > f[j][k]) f[j][k+t] = f[j][k];
					} else {
						if (f[j][t] > f[j][0]) f[j][t] = f[j][0] + h;
					}
				}
			}
			tmax += t;
		}
		int ans = INF, t;
		for (int j = 1; j <= tmax; ++j) {
			for (int k = tmax - j; k >= 1; --k) {
				if (f[j][k] >= INF) continue;
				t = (f[j][k] + b[0].h) * max(tsum - j - k, max(j, k));
				if (ans > t) ans = t;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
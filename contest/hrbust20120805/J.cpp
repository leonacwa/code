/* Walk
 * 尼玛，完全看不懂题意，看完别人的源代码后才看明白的
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MaxN = 2505;
const double eps = 1e-8;

struct Point {
	int x, y;
};
Point pl[MaxN][2005];
int psz[MaxN], ht[MaxN];
int inter[MaxN], idx[MaxN];
double left_most[MaxN];

bool cmp(int a, int b) {
	return left_most[a] < left_most[b];
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &ht[i], &psz[i]);
			for (int j = 0; j < psz[i]; ++j) {
				scanf("%d%d", &pl[i][j].x, &pl[i][j].y);
			}
			pl[i][psz[i]] = pl[i][0];
		}
		for (int i = 0; i < n; ++i) {
			left_most[i] = 1e100, idx[i] = i, inter[i] = 0;
			for (int j = 0; j < psz[i]; ++j) {
				if (pl[i][j].y == pl[i][j+1].y) continue;
				double x1 = pl[i][j].x, y1 = pl[i][j].y, x2 = pl[i][j+1].x, y2 = pl[i][j+1].y;
				if (y1 > y2) {
					swap(x1, x2), swap(y1, y2);
				}
				if (!(y1 <= 0+eps && 0 <= y2-eps)) continue;
				double x = (x2 - x1) * (0 - y1) / (y2 - y1) + x1;
				if (x < 0.0 || x > 1e5) continue;
				++inter[i];
				if (left_most[i] > x) left_most[i] = x;
			}
		}
		sort(idx, idx + n, cmp);
		int pre_h = -1, up = 0, down = 0;
		for (int i = 0; i < n; ++i) {
			if (inter[idx[i]] % 2 == 0) continue;
			if (ht[idx[i]] == pre_h) continue;
			if (pre_h != -1) {
				int dh = ht[idx[i]] - pre_h;
				if (dh > 0) up += dh;
				else down -= dh;
			}
			pre_h = ht[idx[i]];
		}
		printf("%d %d\n", up, down);
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

struct Board {
	int x[2], h;
	int f[2];
};
bool cmph(const Board &a, const Board &b)
{
	return a.h > b.h;
}
Board b[1005];

int main()
{
	int nTest;
	int x, y, n, MAX;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d %d %d", &n, &x, &y, &MAX);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d %d", &b[i].x[0], &b[i].x[1], &b[i].h);
		}
		sort(b, b+n, cmph);
		int can = 1;
		int ans = INT_MAX;
		for (int i = 0; i < n; ++i) {
			b[i].f[0] = INT_MAX;
			b[i].f[1] = INT_MAX;
			if (can && y >= b[i].h && y - b[i].h <= MAX && b[i].x[0] <= x && x <= b[i].x[1]) {
				b[i].f[0] = y - b[i].h + abs(b[i].x[0] - x);
				b[i].f[1] = y - b[i].h + abs(b[i].x[1] - x);
				can = 0;
			}
		}
		if (can && y <= MAX) {
			ans = y;
		} else {
			for (int i = 0; i < n; ++i) {
				if (b[i].f[0] >= INT_MAX) continue;
				int x, y = b[i].h;
				for (int k = 0; k < 2; ++k) {
					x = b[i].x[k];
					can = 1;
					for (int j = i+1; j < n; ++j) {
						if (y - b[j].h > MAX) break;
						if (b[j].x[0] <= x && x <= b[j].x[1]) {
							b[j].f[0] = min(b[j].f[0], b[i].f[k] + y - b[j].h + abs(b[j].x[0] - x));
							b[j].f[1] = min(b[j].f[1], b[i].f[k] + y - b[j].h + abs(b[j].x[1] - x));
							can = 0;
							break;
						}
					}
					if (can && y <= MAX) {
						ans = min(ans, b[i].f[k] + y);
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


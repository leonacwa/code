#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int t, w, now, pre, tr;
int f[2][2][31];

int main()
{
	while (EOF != scanf("%d %d", &t, &w)) {
		memset(f, -1, sizeof(f));
		f[0][0][0] = 0;
		for (int i = 1; i <= t; ++i) {
			scanf("%d", &tr);
			--tr;
			now = i % 2, pre = (i - 1) % 2;
			for (int j = 0; j <= 1; ++j) {
				for (int k = 0; k <= w; ++k) {
					f[now][j][k] = f[pre][j][k];
					if (k > 0) {
						f[now][j][k] = max(f[now][j][k], f[pre][1 - j][k-1]);
					}
					if (tr == j && f[now][j][k] != -1) {
						++f[now][j][k];
					}
				}
			}
		}
		now = t % 2;
		int ans = 0;
		for (int j = 0; j <= 1; ++j) {
			for (int k = 0; k <= w; ++k) {
				if (ans < f[now][j][k]) {
					ans = f[now][j][k];
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


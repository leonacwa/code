#include <cstdio>
#include <cstring>

const int MAXN = 301;
int a[MAXN], b[MAXN];
bool vis[MAXN];

int main() {
	int n;
	while (EOF != scanf("%d", &n) && n) {
		int end = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &a[i], &b[i]);
			if (end < b[i]) end = b[i];
		}
		int ans = 0;
		for (int i = 0; i < 5; ++i) {
			memset(vis, 0, sizeof(vis));
			int t = 0;
			for (int j = i; j <= end; j += 5) {
				int p = -1;
				for (int k = 0; k < n; ++k) {
					if (!vis[k] && a[k] <= j && j < b[k]) {
						if (p == -1 || b[p] > b[k]) p = k;
					}
				}
				if (p != -1) {
					vis[p] = true;
					++t;
				}
			}
			if (ans < t) ans = t;
		}
		printf("%d\n", ans);
	}
	return 0;
}

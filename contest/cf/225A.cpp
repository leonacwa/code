/* #139-2 A. Dice Tower
 * */
#include <cstdio>
#include <cstring>

bool u[7];
int main() {
	int n, a, b, bt;
	while (EOF != scanf("%d", &n)) {
		scanf("%d", &bt);
		bt = 7 - bt;
		scanf("%d%d", &a, &b);
		bool ans = true;
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &a, &b);
			if (!ans) continue;
			memset(u, 0, sizeof(u));
			u[a] = u[7-a] = u[b] = u[7-b] = u[bt] = true;
			int cnt = 0;
			for (int j = 1; j <= 6; ++j) {
				if (!u[j]) {
					++cnt;
					bt = 7 - j;
				}
			}
			if (cnt > 1) ans = false;
		}
		puts(ans ? "YES" : "NO");
	}
	return 0;
}

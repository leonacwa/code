/* Card
 * */
#include <cstdio>
#include <cstring>

int m[1000000][52];

int main() {
	int runs;
	scanf("%d", &runs);
	for (int run = 1; run <= runs; ++run) {
		for (int i = 0; i < 52; ++i) scanf("%d", &m[0][i]);
		int n, l, r;
		scanf("%d%d%d", &n, &l, &r);
		--l, --r;
		int c = 0;
		while (1) {
			int j = 0;
			for (int i = l; i <= r; ++i) m[c+1][j++] = m[c][i];
			for (int i = 0; i < l; ++i) m[c+1][j++] = m[c][i];
			for (int i = r+1; i < 52; ++i) m[c+1][j++] = m[c][i];
			++c;

			bool eq = true;
			for (int i = 0; i <= r; ++i) {
				if (m[c][i] != m[0][i]) {
					eq = false;
					break;
				}
			}
			if (eq) break;
		}
		n %= c;
		printf("Case #%d:", run);
		for (int i = 0; i < 52; ++i) {
			printf(" %d", m[n][i]);
		}
		puts("");
	}
	return 0;
}

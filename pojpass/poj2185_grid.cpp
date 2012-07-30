/* poj2185 Milking Grid
 * */
#include <cstdio>
#include <cstring>

const int MAXR = 10005, MAXC = 80;
char row[MAXR][MAXC], col[MAXC][MAXR];
int ext[MAXR + MAXC], next[MAXR + MAXC];
int f[MAXR + MAXC];

void get_next(int lt, char t[], int next[]) {
	int i, j, p, k;
	next[0] = lt;
	k = 1;
	j = -1;
	for (i = 1; i < lt; ++i, --j) {
		if (j < 0 || i + next[i - k] >= p) {
			if (j < 0) j = 0, p = i;
			while (p < lt && t[p] == t[j]) ++j, ++p;
			next[i] = j, k = i;
		}
		else next[i] = next[i - k];
	}
	next[lt] = 0;
}

int main()
{
	int R, C;
	while (EOF != scanf("%d%d", &R, &C)) {
		for (int i = 0; i < R; ++i) {
			scanf("%s", row[i]);
			for (int j = 0; j < C; ++j) col[j][i] = row[i][j];
		}
		for (int j = 0; j < C; ++j) col[j][R] = 0;
		memset(f, 0, sizeof(f));
		for (int i = 0; i < R; ++i) {
			get_next(C, row[i], next);
			for (int j = 1; j <= C; ++j) {
				if (next[j] == C - j) ++f[j];
			}
		}
		int r = C;
		for (int j = 1; j <= C; ++j) {
			if (f[j] == R) {
				r = j;
				break;
			}
		}
		memset(f, 0, sizeof(f));
		for (int i = 0; i < C; ++i) {
			get_next(R, col[i], next);
			for (int j = 1; j <= R; ++j) {
				if (next[j] == R - j) ++f[j];
			}
		}
		int c = R;
		for (int j = 1; j <= R; ++j) {
			if (f[j] == C) {
				c = j;
				break;
			}
		}
		printf("%d\n", r * c);
	}
	return 0;
}

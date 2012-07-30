/* poj2185 Milking Grid
 * */
#include <cstdio>
#include <cstring>

const int MAXR = 10005, MAXC = 80;
char row[MAXR][MAXC], col[MAXC][MAXR];
int ext[MAXR + MAXC], next[MAXR + MAXC];
int f[MAXR + MAXC];

void get_next(int lt, char t[], int next[]) {
	int i, j, a, p, k,len;
	next[0] = lt;
	j = 0;
	while (1+j < lt && t[j] == t[1+j]) ++j;
	next[1] = j;
	k = 1;
	for (i = 2; i < lt; ++i) {
		p = k + next[k] - 1;
		len = next[i - k];
		if (i + len - 1 < p) next[i] = len;
		else {
			j = p - i + 1;
			if (j < 0) j = 0;
			while (i+j < lt && t[i+j] == t[j]) ++j;
			next[i] = j;
			k = i;
		}
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

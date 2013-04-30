/*
 * CF 259 A. Little Elephant and Chess
 * */
#include <cstdio>
#include <cstring>

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

char ma[8][9];

bool check(int s, int h) {
	if (ma[0][0] != 'W') return 0;
	for (int i = s; i < h; ++i) {
		for (int j = 0; j < 8; ++j) {
			for (int k = 0; k < 4; ++k) {
				int x = i + dx[k], y = j + dy[k];
				if (0 <= x && x < h && 0 <= y && y < 8) {
					if (ma[i][j] == ma[x][y]) return 0;
				}
			}
		}
	}
	return 1;
}

bool dfs(int k) {
	if (k > 0 && ma[0][0] != 'W') return 0;
	if (k > 0 && !check(k-1, k)) return 0;
	if (k == 8) {
		return check(0, 8);
	}
	char ch;
	for (int i = 0; i < 8; ++i) {
		if (dfs(k+1)) return 1;
		ch = ma[k][7];
		for (int j = 7; j > 0; --j) {
			ma[k][j] = ma[k][j-1];
		}
		ma[k][0] = ch;
	}
	return 0;
}

int main() {
	while (EOF != scanf("%s", ma[0])) {
		for (int i = 1; i < 8; ++i) {
			scanf("%s", ma[i]);
		}
		puts(dfs(0) ? "YES" : "NO");
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <cctype>

const int AC = 2, PE = 3, WA = 4;

const int ans[8][8] = {
	{0, 1, 2, 2, 2, 2, 2, 2},
	{1, 2, 4, 4, 5, 6, 7, 8},
	{2, 4, 6, 8, 10, 12, 14, 16},
	{2, 4, 8, 9, 11, 14, 16, 18},
	{2, 5, 10, 11, 14, 18, 20, 23},
	{2, 6, 12, 14, 18, 22, 26, 30},
	{2, 7, 14, 16, 20, 26, 29, 33},
	{2, 8, 16, 18, 23, 30, 33, 38}
};
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int l, w;
char m[9][9];
bool vis[8][8];

int dfs(int x, int y) {
	if (vis[x][y]) return 0;
	vis[x][y] = true;
	if (m[x][y] == 'B') {
		return 1;
	}
	int s = 0;
	for (int i = 0, x2, y2; i < 4; ++i) {
		x2 = x + dx[i], y2 = y + dy[i];
		if (x2 < 0 || x2 >= l || y2 < 0 || y2 >= w) continue;
		s += dfs(x2, y2);
	}
	return s;
}

int main(int argc, char * argv[]) {
	if (argc != 4) return -1;
	FILE *din = freopen(argv[1], "r", stdin);
	//FILE *dout = fopen(argv[2], "r");
	FILE *uout = fopen(argv[3], "r");
	int runs, res = AC;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d%d", &l, &w);
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j <= w; ++j) {
				char ch = fgetc(uout);
				if (ch == EOF && (!(i+1 == l && j == w))) {
					res = WA;
					goto End;
				}
				if (ch == '\n' && j != w) {
					res = PE;
				} else if (ch != '\n' && j == w) {
					res = PE;
					ungetc(ch, uout);
				} else m[i][j] = ch;
			}
			m[i][w] = 0;
		}
		int ex = -1, ey = -1;
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j < w; ++j) {
				if (m[i][j] == 'E') {
					if (ex != -1 && ey != -1) {
						res = WA;
						goto End;
					}
					ex = i, ey = j;
				} else if (m[i][j] != 'E' && m[i][j] != 'B' && m[i][j] != '.') {
					res = WA;
					goto End;
				}
			}
		}
		if (ex == -1 && ey == -1) {
			res = WA;
			goto End;
		}
		memset(vis, 0, sizeof(vis));
		int cnt = dfs(ex, ey);
		if (cnt != ans[l-1][w-1]) {
			res = WA;
			goto End;
		}
	}
	char ch;
	while (EOF != (ch = fgetc(uout))) {
		if (!isspace(ch)) {
			res = WA;
			goto End;
		}
		res = PE;
	}
End:
	printf("%d\n", res);
	fclose(din);
	fclose(uout);
	return 0;
}

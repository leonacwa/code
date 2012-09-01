/* Minesweeper
 * */
#include <cstdio>
#include <cstring>

const int 
	dx[8] = {-1, -1, -1, 0, 1, 1,  1,  0}, 
	dy[8] = {-1,  0,  1, 1, 1, 0, -1, -1};

int n, m;
char mat[25][25];
bool vis[25][25];

int count_f(int x, int y) {
	int s = 0;
	for (int i = 0; i < 8; ++i) {
		int a = x + dx[i], b = y + dy[i];
		if (0 <= a && a < n && 0 <= b && b < m) {
			if (mat[a][b] == 'F') {
				++s;
				vis[a][b] = true;
			}
		}
	}
	return s;
}

bool check_x(int x, int y) {
	int s = 0, total = 0;
	for (int i = 0; i < 8; ++i) {
		int a = x + dx[i], b = y + dy[i];
		if (0 <= a && a < n && 0 <= b && b < m) {
			if (mat[a][b] == 'F') continue;
			++total;
			if (mat[a][b] > '0') ++s;
		}
	}
	return s == total;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) scanf("%s", mat[i]);
		bool ans = true;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (mat[i][j] == 'F') {
					if (!check_x(i, j)) {
						ans = false;
						break;
					}
				} else {
					if (count_f(i, j) != mat[i][j] - '0') {
						ans = false;
						break;
					}
				}
			}
			if (!ans) break;
		}
		int cnt_vis = 0, cnt_flag = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (vis[i][j]) ++cnt_vis;
				if (mat[i][j] == 'F') ++cnt_flag;
			}
		}
		if (ans && cnt_vis != cnt_flag) ans = false;
		puts(ans ? "Well done Clark!" : "Please sweep the mine again!");
	}
	return 0;
}

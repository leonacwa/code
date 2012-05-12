#include <stdio.h>

const int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dx4[4] = {-1, 0, 1, 0}, dy4[4] = {0, 1, 0, -1};
const int NN = 21;
char ma[NN][NN];
int r, c, x, y;

int dfs(int x, int y)
{
	int ret = 0, i, tx, ty;
	if (ma[x][y] == '.') return 0;
	ma[x][y] = 'x';
	for (i = 0; i < 4; ++i) {
		tx = x + dx4[i];
		ty = y + dy4[i];
		if (tx < 0 || r <= tx || ty < 0 || c <= ty || ma[tx][ty] == '.') {
			++ret;
		}
	}
	for (i = 0; i < 8; ++i) {
		tx = x + dx[i];
		ty = y + dy[i];
		if (0 <= tx && tx < r && 0 <= ty && ty < c && ma[tx][ty] == 'X') {
			ret += dfs(tx, ty);
		}
	}
	return ret;
}

int main()
{
	int i;
	while (EOF != scanf("%d %d %d %d", &r, &c, &x, &y) && r > 0 && c > 0 && x > 0 && y > 0) {
		for (i = 0; i < r; ++i) {
			scanf("%s", ma[i]);
		}
		printf("%d\n", dfs(x-1, y-1));
	}	
	return 0;
}


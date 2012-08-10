#include <cstdio>
#include <cstring>
#include <climits>

typedef unsigned int uint;
typedef long long int64;

const int MAXN = 1001;
const uint MOD = 0x7fffffff;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

char mat[MAXN][MAXN];
uint f[MAXN][MAXN];
int mem[MAXN][MAXN];

struct XY {
	int x, y;
	XY() {}
	XY(int tx, int ty) : x(tx), y(ty) {}
} que[MAXN * MAXN * 2];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) scanf("%s", mat[i]);
		memset(f, 0, sizeof(f));
		if (mat[0][0] == '.' && mat[n-1][n-1] == '.') {
			f[0][0] = 1;
			for (int j = 1; j < n; ++j) {
				if (mat[0][j] == '.') f[0][j] = f[0][j-1];
			}
			for (int i = 1; i < n; ++i) {
				if (mat[i][0] == '.') {
					f[i][0] = f[i-1][0];
				}
				for (int j = 1; j < n; ++j) {
					if (mat[i][j] == '.') {
						f[i][j] = f[i-1][j] + f[i][j-1];
						f[i][j] %= MOD;
					}
				}
			}
		}
		if (f[n-1][n-1] > 0) {
			printf("%u\n", f[n-1][n-1]);
		} else {
			memset(mem, -1, sizeof(mem));
			XY *fr = que, *ta = que;
			if (mat[0][0] == '.') {
				*ta++ = XY(0, 0);
				mem[0][0] = 0;
			}
			while (fr < ta) {
				XY c = *fr++;
				int st = mem[c.x][c.y] + 1;
				for (int i  = 0; i < 4; ++i) {
					int x = c.x + dx[i], y = c.y + dy[i];
					if (0 <= x && x < n && 0 <= y && y < n 
							&& mat[x][y] == '.' && (mem[x][y] == -1)) {
						*ta++ = XY(x, y);
						mem[x][y] = st;
					}
				}
			}
			if (mem[n-1][n-1] != -1) {
				puts("THE GAME IS A LIE");
			} else {
				puts("INCONCEIVABLE");
			}
		}
	}
	return 0;
}

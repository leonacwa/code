/* C. Barcode
 * DP题
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1005;

char str[N];
int w[N];
int f[N][N][2];

int main() {
	int n, m, x, y;
	while (EOF != scanf("%d%d%d%d", &n, &m, &x, &y)) {
		memset(w, 0, sizeof(w));
		for (int i = 0; i < n; ++i) {
			scanf("%s", str);
			for (int j = 0; j < m; ++j) {
				if (str[j] == '.') ++w[j];
			}
		}
		memset(f, 0x1f, sizeof(f));
		f[0][1][0] = n - w[0];
		f[0][1][1] = w[0];
		for (int i = 1; i < m; ++i) {
			for (int c = 0; c <= 1; ++c) {
				int t = c ? w[i] : n - w[i];
				for (int j = 1; j <= y; ++j) {
					if (x <= j && j <= y) f[i][1][c] = min(f[i][1][c], f[i-1][j][!c] + t);
					f[i][j][c] = min(f[i][j][c], f[i-1][j-1][c] + t);
				}
			}
		}
		int ans = min(f[m-1][x][0], f[m-1][x][1]);
		for (int i = x+1; i <= y; ++i) {
			ans = min(ans, min(f[m-1][i][0], f[m-1][i][1]));
		}
		printf("%d\n", ans);
	}
}


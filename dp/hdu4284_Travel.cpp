/* HDU 4284 Travel
 * Floyd + 状态DP
 * 这个是循环判断合法状态来扩展
 * */
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 101;

int id[MAXN], id2[MAXN];
int C[MAXN], D[MAXN];
int g[MAXN][MAXN];
int f[1<<15][15];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m, money;
		scanf("%d%d%d", &n, &m, &money);
		memset(g, -1, sizeof(g));
		for (int i = 0; i <= n; ++i) g[i][i] = 0;
		for (int i = 0, u, v, w; i < m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			--u, --v;
			if (g[u][v] == -1 || g[u][v] > w) g[u][v] = g[v][u] = w;
		}
		int h;
		scanf("%d", &h);
		for (int i = 0; i < h; ++i) {
			int num, c, d;
			scanf("%d%d%d", &num, &c, &d);
			--num;
			id[num] = i;
			id2[i] = num;
			C[i] = c;
			D[i] = d;
		}

		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) 
				for (int j = 0; j < n; ++j) {
					if (g[i][k] != -1 && g[k][j] != -1) {
						int t = g[i][k] + g[k][j];
						if (g[i][j] == -1 || g[i][j] > t) g[i][j] = t;
					}
				}
		}
		memset(f, -1, sizeof(f));
		for (int i = 0; i < h; ++i) {
			if (money >= g[0][ id2[i] ] + D[i] && g[0][ id2[i] ] != -1) {
				f[1<<i][i] = money - g[0][ id2[i] ] - D[i] + C[i];
			}
		}
		int all = (1<<h) - 1;
		for (int os = 1; os <= all; ++os) {
			for (int oi = 0; oi < h; ++oi) {
				if (!(os & (1<<oi)) || f[os][oi] < 0) continue;
				for (int i = 0; i < h; ++i) {
					if (os & (1<<i)) continue;
					int s = os | (1<<i);
					int fm = f[os][oi];
					if (fm >= g[ id2[oi] ][ id2[i] ] + D[i]) {
						int t = fm - g[ id2[oi] ][ id2[i] ] - D[i] + C[i];
						if (t >= 0 && (f[s][i] < 0 || f[s][i] < t)) {
							f[s][i] = t;
						}
					}
				}
			}
		}
		int ans = -1;
		for (int i = 0; i < h; ++i) {
			if (f[all][i] < 0) continue;
			if (f[all][i] >= g[ id2[i] ][ 0 ]) {
				ans = 1;
				break;
			}
		}
		if (ans < 0) puts("NO");
		else puts("YES");
	}
	return 0;
}

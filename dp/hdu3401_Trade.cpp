/* HDU 3401 Trade
 * DP + 单调队列优化
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2005, INF = 0x3fffffff;

int ap[MAXN], bp[MAXN], as[MAXN], bs[MAXN];
int f[MAXN][MAXN];
int q[MAXN];

template<class T>
void check_max(T &a, const T &b) {
	if (a < b) a = b;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, mp, w;
		scanf("%d%d%d", &n, &mp, &w);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d%d", &ap[i], &bp[i], &as[i], &bs[i]);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= as[i]; ++j) f[i][j] = -j * ap[i];
			for (int j = as[i] + 1; j <= mp; ++j) f[i][j] = -INF;
		}
		for (int i = 2; i <= n; ++i) {
			for (int j = 0; j <= mp; ++j) check_max(f[i][j], f[i-1][j]);
			if (i - w - 1 <= 0) continue;
			int fr = 0, ta = 1, pr = i - w - 1;
			q[0] = 0;
			for (int j = 1; j <= mp; ++j) {
				while (fr < ta && j - q[fr] > as[i]) ++fr;
				if (fr < ta) check_max(f[i][j], f[pr][q[fr]] - ap[i] * (j - q[fr]));
				while (fr < ta && f[pr][q[ta-1]] + ap[i] * q[ta-1] <= f[pr][j] + ap[i] * j) --ta;
				q[ta++] = j;
			}
			fr = 0, ta = 1;
			q[0] = mp;
			for (int j = mp-1; j >= 0; --j) {
				while (fr < ta && q[fr] - j > bs[i]) ++fr;
				if (fr < ta) check_max(f[i][j], f[pr][q[fr]] + bp[i] * (q[fr] - j));
				while (fr < ta && f[pr][q[ta-1]] + bp[i] * q[ta-1] <= f[pr][j] + bp[i] * j) --ta;
				q[ta++] = j;
			}
		}
		int ans = -INF;
		for (int j = 0; j <= mp; ++j) {
			if (ans < f[n][j]) ans = f[n][j];
		}
		printf("%d\n", ans);
	}
	return 0;
}

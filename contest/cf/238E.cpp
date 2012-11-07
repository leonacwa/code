/*
 * CF 238 E. Meeting Her
 * */
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int B_INF = 0x3f;
const int MAXN = 105;

int g[MAXN][MAXN];
int s[MAXN], t[MAXN];
int ans[MAXN], bs[MAXN];
bool can[MAXN][MAXN];

int main() {
	int n, m, a, b, k;
	scanf("%d%d%d%d", &n, &m, &a, &b);
	--a, --b;
	memset(g, B_INF, sizeof(g));
	for (int i = 0, u, v; i < m; ++i) {
		scanf("%d%d", &u, &v);
		--u, --v;
		g[u][v] = 1;
	}
	for (int i = 0; i < n; ++i) g[i][i] = 0;
	for (int l = 0; l < n; ++l) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (g[i][j] > g[i][l] + g[l][j]) g[i][j] = g[i][l] + g[l][j];
			}
		}
	}
	scanf("%d", &k);
	for (int i = 0; i < k; ++i) {
		scanf("%d%d", &s[i], &t[i]);
		--s[i], --t[i];
		if (g[s[i]][t[i]] >= INF) --i, --k;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			if (g[s[j]][i] + g[i][t[j]] == g[s[j]][t[j]]) {
				int cnt = 0;
				for (int ii = 0; ii < n; ++ii) {
					if (g[ii][t[j]] < INF && g[s[j]][t[j]] == g[s[j]][ii] + g[ii][t[j]] && g[ii][ t[j] ] == g[i][ t[j] ]) {
						++cnt;
					}
				}
				can[i][j] = (cnt == 1);
			}
		}
	}
	memset(ans, B_INF, sizeof(ans));
	ans[b] = 0;
	memset(bs, B_INF, sizeof(bs));
	bool go = true;
	while (go) {
		go = false;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < k; ++j) {
				if (can[i][j]) {
					vector< pair<int, int> > vp;
					for (int l = 0; l < n; ++l) {
						if (g[l][t[j]] < INF && g[s[j]][t[j]] == g[s[j]][l] + g[l][t[j]] && g[i][t[j]] >= g[l][t[j]]) {
							vp.push_back(make_pair(g[l][t[j]], l));
						}
					}
					sort(vp.begin(), vp.end());
					int sz = vp.size();
					for (int z = 0; z < sz; ++z) {
						int x = vp[z].second;
						bs[x] = ans[x];
						if (z == 0) continue;
						int w = 0;
						for (int y = 0; y < n; ++y) {
							if (g[x][y] == 1 && g[x][t[j]] == 1 + g[y][t[j]]) {
								w = max(w, bs[y]);
							}
						}
						bs[x] = min(bs[x], w);
					}
					if (ans[i] > bs[i] + 1) {
						ans[i] = bs[i] + 1;
						go = true;
					}
				}
			}
		}
	}
	if (ans[a] >= INF) puts("-1");
	else printf("%d\n", ans[a]);
	return 0;
}

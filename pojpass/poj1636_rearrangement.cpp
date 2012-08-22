/* Prison rearrangement
 * 给每对危险囚犯连一条无向边，那么每个连通分量中，A和B集合的囚犯不能再同一个集合内，要换就要一起换，可以DFS求出这些连通分量。
 * 然后DP。因为连通分量中A，B集合内的囚犯必须互换，题目又要求交换人数一样，那么用f[i][j]数组表示互换i,j人是否可行。
 * 因为连通分量必须整体互换，对于第k个连通分量，A的人数为nA[k], B为nB[k]，那么可以有 f[i+nA[k]][j+nB[k]] = f[i][j] == true
 * */
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 205;
vector<int> g[MAXN<<1];
int n, m, g1, g2, tot, n1[MAXN], n2[MAXN];
bool f[MAXN][MAXN], vis[MAXN<<1];

void dfs(int i) {
	vis[i] = true;
	if (i < n) ++g1;
	else ++g2;
	for (int j = g[i].size()-1; j >= 0; --j) {
		if (!vis[g[i][j]]) dfs(g[i][j]);
	}
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) g[i].clear(), g[i+n].clear();
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			--a, --b;
			g[a].push_back(b + n);
			g[b+n].push_back(a);
		}
		memset(vis, 0, sizeof(vis));
		tot = 0;
		for (int i = 0; i < 2*n; ++i) {
			if (!vis[i]) {
				g1 = g2 = 0;
				dfs(i);
				n1[tot] = g1;
				n2[tot] = g2;
				++tot;
			}
		}
		memset(f, 0, sizeof(f));
		f[0][0] = true;
		for (int i = 0; i < tot; ++i) {
			for (int j = n/2; j >= n1[i]; --j) {
				for (int k = n/2; k >= n2[i]; --k) {
					if (f[j-n1[i]][k-n2[i]] && !f[j][k]) f[j][k] = true;
				}
			}
		}
		int i = n / 2;
		for (; i > 0; --i) {
			if (f[i][i]) break;
		}
		printf("%d\n", i);
	}
	return 0;
}

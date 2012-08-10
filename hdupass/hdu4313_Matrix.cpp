/* HDU 4313 Matrix
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int tu, int tv, int tw) : u(tu), v(tv), w(tw) {}
	bool operator < (const Edge &B) const {
		return w > B.w;
	}
} E[MAXN];

int fa[MAXN];
bool isd[MAXN];
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		fa[fy] = fx;
		if (isd[fy]) isd[fx] = true;
	}
}

int main()
{
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, k;
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n-1; ++i) {
			scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
		}
		memset(isd, 0, sizeof(isd));
		for (int i = 0, a; i < k; ++i) {
			scanf("%d", &a);
			isd[a] = true;
		}
		for (int i = 0; i <= n; ++i) fa[i] = i;
		sort(E, E + n-1);
		long long ans = 0;
		for (int i = 0; i < n-1; ++i) {
			int fu = find(E[i].u), fv = find(E[i].v);
			if (isd[fu] && isd[fv]) {
				ans += E[i].w;
			} else {
				join(fu, fv);
			}
		}
		printf("%I64d\n", ans);
	}
	return 0;
}

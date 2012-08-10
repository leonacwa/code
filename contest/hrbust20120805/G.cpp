/* Summits
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 500 * 500 + 10;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int ht[MAXN];
int idx[MAXN];

int fa[MAXN];
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (ht[fx] < ht[fy]) swap(fx, fy);
	if (fx != fy) {
		fa[fy] = fx;
	}
}
bool cmph(int a, int b) {
	return ht[a] > ht[b];
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int h, w, d;
		scanf("%d%d%d", &h, &w, &d);
		int tot = h * w;
		for (int i = 0; i < tot; ++i) {
			scanf("%d", &ht[i]);
			idx[i] = i, fa[i] = i;
		}
		sort(idx, idx + tot, cmph);
		int ans = 0;
		for (int i = 0, j = 0, s, t; i < tot; ++i) {
			for (s = idx[i]; j < tot && ht[t=idx[j]]+d > ht[s]; ++j) {
				int x = t / w, y = t % w;
				for (int k = 0, x2, y2; k < 4; ++k) {
					x2 = x + dx[k], y2 = y + dy[k];
					if (x2 < 0 || x2 >= h || y2 < 0 || y2 >= w || ht[x2*w+y2] < ht[t]) continue;
					join(x2*w+y2, t);
				}
			}
			if (ht[s] >= ht[find(s)]) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}

/* POJ 2823 Sliding Window
 * 单调队列的应用
 * */
#include <cstdio>
#include <cstring>
const int MAXN = 1000005;
struct Node {
	int p, v;
	Node() {}
	Node(int a, int b) {p = a, v = b;}
} minq[MAXN], maxq[MAXN];
int ans[MAXN][2];

int main() {
	int n, k, fa, fb, ta, tb, cnt;
	while (EOF != scanf("%d%d", &n, &k)) {
		cnt = fa = fb = ta = tb = 0;
		for (int i = 0, v; i < k-1 && i < n; ++i) {
			scanf("%d", &v);
			Node nd(i, v);
			while (fa < ta && minq[ta-1].v >= v) --ta;
			minq[ta++] = nd;
			while (fb < tb && maxq[tb-1].v <= v) --tb;
			maxq[tb++] = nd;
		}
		for (int i = k-1, v; i < n; ++i) {
			scanf("%d", &v);
			Node nd(i, v);
			while (fa < ta && minq[fa].p < i-k+1) ++fa;
			while (fa < ta && minq[ta-1].v >= v) --ta;
			minq[ta++] = nd;
			while (fb < tb && maxq[fb].p < i-k+1) ++fb;
			while (fb < tb && maxq[tb-1].v <= v) --tb;
			maxq[tb++] = nd;
			ans[cnt][0] = minq[fa].v;
			ans[cnt][1] = maxq[fb].v;
			++cnt;
		}
		printf("%d", ans[0][0]);
		for (int i = 1; i < cnt; ++i) printf(" %d", ans[i][0]);
		puts("");
		printf("%d", ans[0][1]);
		for (int i = 1; i < cnt; ++i) printf(" %d", ans[i][1]);
		puts("");
	}
	return 0;
}

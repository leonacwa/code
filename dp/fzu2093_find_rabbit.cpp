/* FZU 2093 寻找兔子
 * 疑问很大，没法AC
 * 对于每个小序列，预处理其本身的最大子段和，和左边连接的最大子段和，和右边连接的最大子段和。
 * 然后对于最终序列，可以用类似求最大子段和的贪心法O（M)处理，M为最终序列的长度。
 * */
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX_N = (1<<15) + 100; 
const int MAX_E = 860000;//(1<<20) + 100; /* 貌似不会超过860000条边 用 15 0 测试的*/

int count1(unsigned int x) {
	int ret = 0;
	while (x) {
		if (x&1) ++ret;
		x >>= 1;
	}
	return ret;
}

struct Arc {
	int to;
	int next;
};
Arc A[MAX_E];
int V[MAX_N];
int nA;
int vis[MAX_N];
int vec[15];
int n, m;

void clear() {
	memset(V, -1, sizeof(V[0])*MAX_N);
	nA = 0;
}
void addArc(int u, int v) {
	A[nA].to = v;
	A[nA].next = V[u];
	V[u] = nA++;	
}

int bfs(int s, int e) {
	int res = -1;
	queue<int> que;
	memset(vis, 0, sizeof(vis));
	que.push(s);
	vis[s] = 1;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		//printf("bfs(%d)\n", u);
		if (u == e) return vis[u];
		if (count1(u) <= 3) return vis[u];

		for (int i = V[u]; i != -1; i = A[i].next) {
			int v = A[i].to;
			if (!vis[v]) {
				vis[v] = vis[u] + 1;
				if (v == e) return vis[v];
				if (count1(v) <= 3) return vis[v];
				que.push(v);
			}
		}
	}
	return res;
}

int go(unsigned int x) {
	int i = 0, ret = 0;
	while (x) {
		if (x&1) ret |= vec[i];
		++i, x >>= 1;
	}
	return ret;
}

void add(int x) {
	if (count1(x) <= 3) {
		addArc(x, 0);
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (!(x&(1<<i))) continue;
		for (int j = i+1; j < n; ++j) {
			if (!(x&(1<<j))) continue;
			int t = x & ~(1<<i) & ~(1<<j);
			int t2 = go(t);
			if (t2 == x) continue;
			addArc(x, t2);
		}
	}
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d%d", &n, &m);
		memset(vec, 0, sizeof(vec));
		clear();
		for (int i = 0; i < m; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			--a, --b;
			vec[a] |= (1<<b);
			vec[b] |= (1<<a);
		}
		for (int i = 0; i < n; ++i) {
			/* 为了特殊处理，比如兔子可能在独立的点上，
			 * 但是这个独立点还没被检测，那么下一步检测的话应该仍包含这些独立点 */
			if (vec[i] == 0) vec[i] |= (1<<i);
		}
		int all = (1<<n) - 1;
		for (int i = all; i > 0; --i) add(i);
	//	printf("nA %d\n", nA);
		int ans = 1;
		if (n > 3) ans = bfs(all, 0);
		printf("%d\n", ans);
	}
	return 0;
}

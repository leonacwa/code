#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int NN = 10005;
struct Edge {
	int v;
	Edge* next;
};
int w[NN];
int maxw[NN];
int nE, n, ans;
Edge *head[NN];
Edge E[NN*2+100];
bool isp[NN];
bool isg[NN];

const int N = 4000000+1;
bool is[N+5];
void getprm(int n){
	int i, j, k = 0;
	int s, e = (int)(sqrt(0.0 + n) + 1);
	memset(is, 1, sizeof(is));
	is[0] = is[1] = 0;
	for (i = 4; i < n; i += 2) is[i] = 0;
	for (i = 3; i < e; i += 2) if (is[i]) {
		for (s = i * 2, j = i * i; j < n; j += s) is[j] = 0;
		// 因为j是奇数，所以+奇数i后是偶数，不必处理！
	}
}

void addEdge(int u, int v)
{
	E[nE].v = v;
	E[nE].next = head[u];
	head[u] = E + nE;
	++nE;
}

void dfs(int p, int pr)
{
	isp[p] = is[w[p]];
	isg[p] = true;
	maxw[p] = w[p];

	for (Edge *e = head[p]; e; e = e->next) {
		int c = e->v;
		if (c == pr) continue;
		dfs(c, p);
		if (false == isp[c]) {
			isp[p] = false;
		}
		if (maxw[p] <= maxw[c]) {
			maxw[p] = maxw[c];
			isg[p] = false;
		}
	}
	if (isp[p] && isg[p]) {
		++ans;
	}
}

int main()
{
	int nCase = 0;
	getprm(N);
	while (EOF != scanf("%d", &n)) {
		memset(head, 0, sizeof(head));
		nE = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", w + i);
		}
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
		}
		ans = 0;
		dfs(1, -1);
		printf("Scenario #%d\n%d\n\n", ++nCase, ans);
	}
	return 0;
}


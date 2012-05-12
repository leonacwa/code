#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int NN = 150000 + 5;
const int KK = 300 + 5;

struct Edge {
	int v;
	struct Edge * next;
};
Edge E[NN];
int nE;
Edge *head[NN];
int wealthy[NN];
int n, k;
int opt[KK];

void addEdge(int u, int v)
{
	E[nE].v = v;
	E[nE].next = head[u];
	head[u] = &E[nE];
	++nE;
}

int dfs(int root, int opt[])
{
	int kk = 0;
	int opt2[KK];
	memset(opt, 0, sizeof(opt[0])*KK);
	for (Edge* cur = head[root]; cur; cur = cur->next) {
		int kk2 = dfs(cur->v, opt2);
		for (int i = kk; i >= 0; --i) {
			for (int j = 0; j <= kk2 && i+j <= k; ++j) {
				opt[i+j] = max(opt[i+j], opt[i] + opt2[j]);
			}
		}
		kk += kk2;
		kk = min(kk, k);
	}
	opt[1] = max(wealthy[root], opt[1]);
	return kk ? kk : 1;
}

int main()
{
	int root, p;
	while (EOF != scanf("%d %d", &n, &k)) {
		nE = 0;
		memset(head, 0, sizeof(head[0])*n);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &p, &wealthy[i]);
			if (p == 0) {
				root = i;
			} else {
				addEdge(p-1, i);
			}
		}
		memset(opt, 0, sizeof(opt));
		int st = dfs(root, opt);
		if (st < k) {
			printf("impossible\n");
		} else {
			printf("%d\n", opt[k]);
		}
	}
	return 0;
}


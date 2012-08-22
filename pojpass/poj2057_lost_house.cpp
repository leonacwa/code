#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 1001;
int n;
int fail[NN], succ[NN], leaf[NN], worm[NN];
struct Child {
	int c, a[8];
} child[NN];

bool cmp(int u, int v)
{
	return (fail[u] + 2) * leaf[v] < (fail[v] + 2) * leaf[u];
}

void dfs(int p)
{
	if (child[p].c == 0) {
		leaf[p] = 1;
		fail[p] = 0;
		succ[p] = 0;
		return;
	}

	leaf[p] = 0;
	for (int i = 0; i < child[p].c; ++i) {
		int c = child[p].a[i];
		dfs(c);
		leaf[p] += leaf[c];
	}
	sort(child[p].a, child[p].a + child[p].c, cmp);
	succ[p] = 0;
	int f = 0;
	for (int i = 0; i < child[p].c; ++i) {
		int c = child[p].a[i];
		succ[p] += (f + 1) * leaf[c] + succ[c];
		f += fail[c] + 2;
	}
	fail[p] = worm[p] ? 0 : f;
}

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 1; i <= n; ++i) child[i].c = 0;
		for (int i = 1; i <= n; ++i) {
			int p;
			char w;
			scanf("%d %c", &p, &w);
			worm[i] = (w == 'Y');
			if (p != -1) {
				child[p].a[child[p].c++] = i;
			}
		}
		dfs(1);
		printf("%.4f\n", (double)succ[1] / leaf[1]);
	}
	return 0;
}


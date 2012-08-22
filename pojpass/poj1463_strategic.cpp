#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct Node {
	int c;
	int a[15];
};
Node node[1505];
int n;
int pr[1505];
int f[1505][2];

void dfs(int k)
{
	int c0 = 0, c1 = 1, a;
	for (int i = 0; i < node[k].c; ++i) {
		a = node[k].a[i];
		dfs(a);
		c0 += f[a][1];
		c1 += min(f[a][0], f[a][1]);
	}
	f[k][0] = c0;
	f[k][1] = c1;
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		memset(pr, -1, sizeof(pr));
		for (int i = 0; i < n; ++i) {
			int k, c, a;
			scanf("%d:(%d)", &k, &c);
			node[k].c = c;
			for (int j = 0; j < c; ++j) {
				scanf("%d", &a);
				pr[a] = k;
				node[k].a[j] = a;
			}
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			if (pr[i] == -1) {
				dfs(i);
				ans += min(f[i][0], f[i][1]);
			}
		}

		printf("%d\n", ans);
	}
	return 0;
}


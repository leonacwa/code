#include <stdio.h>

const int MAXN = 2000 + 5;
int f[MAXN], rel[MAXN];

void init(int n)
{
	for (int i = 0; i <= n; i++) {
		f[i] = i;
		rel[i] = 0;
	}
}

int find(int x)
{
	if (x != f[x]) {
		int t = f[x];
		f[x] = find(f[x]);
		rel[x] = (rel[x] + rel[t]) % 2;
	}
	return f[x];
}

void union_set(int a, int b) // a, b are different gender
{
	int fa = find(a), fb = find(b);
	if (fa != fb) {
		f[fb] = fa;
		rel[fb] = (rel[a] - rel[b] + 1 + 2) % 2;
	}
}

int main()
{
	int caseN;
	scanf("%d", &caseN);
	for (int cs = 1; cs <= caseN; cs++) {
		int n, m;
		bool found = false;
		scanf("%d %d", &n, &m);
		init(n);
		for (int i = 0, a, b; i < m; i++) {
			scanf("%d %d", &a, &b);
			int ta = find(a), tb = find(b);
			if (ta != tb) {
				union_set(a, b);
			} else if (rel[a] == rel[b]) {
				found = true;
			}
		}
		printf("Scenario #%d:\n", cs);
		printf("%s\n", found ? "Suspicious bugs found!" : "No suspicious bugs found!");
		if (cs < caseN) {
			printf("\n");
		}
	}
	return 0;
}


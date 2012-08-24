#include <stdio.h>

int f[10000+5];
int n, m;

void init(int n)
{
	for (int i = 0; i <= n; i++) {
		f[i] = i;
	}
}

int find(int x)
{
	if (x == f[x]) {
		return x;
	}
	return f[x] = find(f[x]);
}

void union_set(int a, int b)
{
	int fa = find(a), fb = find(b);
	if (fa != fb) {
		f[fb] = fa;
	}
}

int main()
{
	int a, b;
	while (EOF != scanf("%d", &n) && n != 0) {
		init(n);
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			union_set(a, b);
		}
		int ans = 0;
		int fp = find(1);
		for (int i = 2; i <= n; i++) {
			int fb = find(i);
			if (fp != fb) {
				ans++;
				union_set(fp, fb);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


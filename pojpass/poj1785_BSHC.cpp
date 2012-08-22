#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 50000 + 10;
struct Node {
	int p;
	char s[26];
};

bool cmp(const Node &A, const Node &B) {
	return strcmp(A.s, B.s) <= 0;
}

Node st[MAXN];
int pr[MAXN], lc[MAXN], rc[MAXN];

void dfs(int r)
{
	if (r == -1) return;
	putchar('(');
	dfs(lc[r]);
	printf("%s", st[r].s);
	dfs(rc[r]);
	putchar(')');
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) {
			scanf("%s", st[i].s);
			st[i].p = atoi(strchr(st[i].s, '/') + 1);
		}
		sort(st, st + n, cmp);
		int r = -1;
		for (int i = 0; i < n; ++i) {
			pr[i] = lc[i] = rc[i] = -1;
			int x = i - 1;
			while (x != -1) {
				if (st[x].p > st[i].p) {
					pr[i] = x;
					rc[x] = i;
					break;
				}
				pr[i] = pr[x];
				rc[x] = lc[i];
				lc[i] = x;
				pr[x] = i;
				x = pr[i];
			}
			if (pr[i] == -1) {
				r = i;
			}
		}
		dfs(r);
		puts("");
	}
	return 0;
}


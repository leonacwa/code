#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

struct Scheme {
	int a[5];
	int p;
};
Scheme sch[100];
int sch_cnt, s;
int co[1000];
int a[5], pr[5];
int f[6][6][6][6][6];

int dfs(int a[])
{
	int b[5];
	for (int i = 0; i < 5; ++i) b[i] = a[i];

	if (f[a[0]][a[1]][a[2]][a[3]][a[4]] != -1) {
		return  f[a[0]][a[1]][a[2]][a[3]][a[4]];
	}
	if (a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0 && a[4] == 0) {
		return f[a[0]][a[1]][a[2]][a[3]][a[4]] = 0;
	}
	f[a[0]][a[1]][a[2]][a[3]][a[4]] = INT_MAX;
	if (a[0] > 0) {
		b[0]--;
		f[a[0]][a[1]][a[2]][a[3]][a[4]] = min(f[a[0]][a[1]][a[2]][a[3]][a[4]], dfs(b) + pr[0]);
		b[0]++;
	}
	if (a[1] > 0) {
		b[1]--;
		f[a[0]][a[1]][a[2]][a[3]][a[4]] = min(f[a[0]][a[1]][a[2]][a[3]][a[4]], dfs(b) + pr[1]);
		b[1]++;
	}
	if (a[2] > 0) {
		b[2]--;
		f[a[0]][a[1]][a[2]][a[3]][a[4]] = min(f[a[0]][a[1]][a[2]][a[3]][a[4]], dfs(b) + pr[2]);
		b[2]++;
	}
	if (a[3] > 0) {
		b[3]--;
		f[a[0]][a[1]][a[2]][a[3]][a[4]] = min(f[a[0]][a[1]][a[2]][a[3]][a[4]], dfs(b) + pr[3]);
		b[3]++;
	}
	if (a[4] > 0) {
		b[4]--;
		f[a[0]][a[1]][a[2]][a[3]][a[4]] = min(f[a[0]][a[1]][a[2]][a[3]][a[4]], dfs(b) + pr[4]);
		b[4]++;
	}
	for (int i = 0; i < sch_cnt; ++i) {
		int *p = sch[i].a;
		if (a[0] >= p[0] && a[1] >= p[1] && a[2] >= p[2] && a[3] >= p[3] && a[4] >= p[4]) {
			b[0] -= p[0], b[1] -= p[1], b[2] -= p[2], b[3] -= p[3], b[4] -= p[4];
			f[a[0]][a[1]][a[2]][a[3]][a[4]] = min(f[a[0]][a[1]][a[2]][a[3]][a[4]], dfs(b) + sch[i].p);
			b[0] += p[0], b[1] += p[1], b[2] += p[2], b[3] += p[3], b[4] += p[4];
		}
	}
	return f[a[0]][a[1]][a[2]][a[3]][a[4]];
}

int main()
{
	int b, c;
	while (EOF != scanf("%d", &b)) {
		memset(co, -1, sizeof(co));
		memset(a, 0, sizeof(a));
		for (int i = 0; i < b; ++i) {
			scanf("%d %d %d", &c, &a[i], &pr[i]);
			co[c] = i;
		}
		sch_cnt = 0;
		scanf("%d", &s);
		for (int i = 0; i < s; ++i) {
			memset(&sch[sch_cnt], 0, sizeof(sch[sch_cnt]));
			int n, c, a, can = 1;
			scanf("%d", &n);
			for (int j = 0; j < n; ++j) {
				scanf("%d %d", &c, &a);
				if (co[c] != -1) sch[sch_cnt].a[co[c]] += a;
				else can = 0;
			}
			scanf("%d", &sch[sch_cnt].p);
			if (can) ++sch_cnt;
		}
		memset(f, -1, sizeof(f));
		printf("%d\n", dfs(a));
	}
	return 0;
}


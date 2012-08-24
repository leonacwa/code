/*
 * hdu 4068
 * SanguoSHA
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 8
struct Hero {
	char s[24];
	char id;
};
Hero h[MAXN];
bool rst[MAXN][MAXN];
int n;

int pl[720+2][MAXN];
bool used[MAXN];
int pl_tmp[MAXN];
int cnt;

bool herocmp(const Hero &a, const Hero &b)
{
	return strcmp(a.s, b.s) < 0;
}

int get_id(char *s)
{
	int l = 0 , r = n-1, mid, ret;
	while (l < r) {
		mid = (l+r) / 2;
		ret = strcmp(s, h[mid].s);
		if (ret <= 0) r = mid;
		else l = mid+1;
	}
	return h[l].id;
}

void dfs(int k)
{
	int i;
	if (k == n) {
		for (i = 0; i < n; ++i) {
			pl[cnt][i] = pl_tmp[i];
		}
		cnt++;
		return;
	}
	for (i = 0; i < n; ++i) {
		if (used[i]) {
			pl_tmp[k] = i;
			used[i] = false;
			dfs(k+1);
			used[i] = true;
		}
	}
}

bool test(int i, int j)
{
	int a = 0, b = 0;
	while (a < n && b < n) {
		if (rst[pl[j][b]][pl[i][a]]) a++;
		else b++;
	}
	return a < b;
}

int solve()
{
	int i, j, k, ts;
	for (i = 0; i < cnt; ++i) {
		for (j = 0; j < cnt; ++j) {
			if (!test(i, j)) break;
		}
		if (j == cnt) return i;
	}
	return -1;
}

int main()
{
	int cs, nCase;
	int i, j, k;
	char str[256];
	scanf("%d", &nCase);
	
	for (cs = 1; cs <= nCase; ++cs) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) scanf("%s", h[i].s);
		sort(h, h+n, herocmp);
		for (i = 0; i < n; ++i)  h[i].id = i;
		memset(rst, false, sizeof(rst));
		for (i = 0; i < n; ++i) {
			scanf("%d", &j);
			for (k = 0; k < j; ++k) {
				scanf("%s", str);
				rst[i][get_id(str)] = true;
			}
		}
		memset(used, true, sizeof(used));
		cnt = 0;
		dfs(0);
		k = solve();
		printf("Case %d: ", cs);
		if (k == -1) {
			printf("No\n");
		}
		else {
			printf("Yes\n");
			for (i = 0; i < n-1; ++i)  printf("%s ", h[pl[k][i]].s);
			printf("%s\n", h[pl[k][i]].s);
		}
	}
	return 0;
}

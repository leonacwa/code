/* 后缀数组应用 
 * 二分枚举最长长度
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int MAXM = 20000 + 10;
const int LOG_MAXM = 18;

int rank[MAXM], sa[MAXM], height[MAXM];
int X[MAXM], Y[MAXM], buc[MAXM];

void cal_height(int *r, int n)
{
	int i, j, k = 0;
	for (i = 1; i <= n; ++i) rank[sa[i]] = i;
	for (i = 0; i < n; height[rank[i++]]=k) {
		for (k?--k:0, j=sa[rank[i]-1]; r[j+k]==r[i+k]; ++k) ;
	}
}

bool cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a+l] == r[b+l];
}

void suffix(int *r, int n, int m)
{
	int i, l, p, *x = X, *y = Y, *t;
	for (i = 0; i < m; ++i) buc[i] = 0;
	for (i = 0; i < n; ++i) buc[x[i]=r[i]]++;
	for (i = 1; i < m; ++i) buc[i] += buc[i-1];
	for (i = n-1; i >= 0; --i) sa[ --buc[x[i]] ] = i;
	for (l = 1, p = 1; p < n; m = p, l <<= 1) {
		for (p = 0, i = n-l; i < n; ++i) y[p++] = i;
		for (i = 0; i < n; ++i) if (sa[i] >= l) y[p++] = sa[i] - l;
		for (i = 0; i < m; ++i) buc[i] = 0;
		for (i = 0; i < n; ++i) buc[ x[y[i]] ]++; 
		for (i = 1; i < m; ++i) buc[i] += buc[i-1];
		for (i = n-1; i >= 0; --i) sa[ --buc[x[y[i]]] ] = y[i];
		for (t=x, x=y, y=t, x[sa[0]]=0, i=1, p=1; i < n; ++i) {
			x[sa[i]] = cmp(y, sa[i-1], sa[i], l) ? p-1 : p++;
		}
	}
	cal_height(r, n-1);
}

int best[MAXM][LOG_MAXM];
void init_rmq(int n)
{
	for (int i = 1; i <= n; ++i) best[i][0] = height[i];
	for (int l = 1; (1 << l) <= n; ++l) {
		int limit = n - (1 << l) + 1;
		for (int i = 1; i <= limit; ++i) {
			best[i][l] = min(best[i][l-1], best[i+(1<<l>>1)][l-1]);
		}
	}
}

int LCP(int a, int b)
{
	if (a > b) swap(a, b);
	++a;
	int l = 0;
	for (; (1 << l) <= b - a + 1; ++l) ;
	--l;
	return min(best[a][l], best[b-(1<<l)+1][l]);
}

int a[MAXM];
int b[MAXM];

int main()
{
	int n, k;
	while (EOF != scanf("%d%d", &n, &k)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		sort(b, b + n);
		map<int, int> xy;
		int id = 0;
		for (int i = 0; i < n; ++i) {
			if (xy[b[i]] == 0) {
				xy[b[i]] = ++id;
			}
		}
		for (int i = 0; i < n; ++i) {
			b[i] = xy[a[i]];
		}
		b[n] = 0;
		suffix(b, n+1, id+1);
		init_rmq(n); 
		int l = 1, r = n, m;
		while (l < r) {
			m = l + (r - l) / 2 + 1;
			int i = 1;
			bool can = false;
			for (int j = i + 1; i < n; ++j) {
				if (j <= n && LCP(i, j) >= m) {
				} else if (j - i < k) {
					i = j;
				} else {
					can = true;
					break;
				}
			}
			if (can) {
				l = m;
			} else {
				r = m - 1;
			}
		}
		printf("%d\n", l);
	}
	return 0;
}


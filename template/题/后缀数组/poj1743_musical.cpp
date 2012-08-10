/*  后缀数组的应用
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXM = 20000 + 10;
const int LOG_MAXM = 20;

int rank[MAXM], sa[MAXM], height[MAXM];
int buc[MAXM], X[MAXM], Y[MAXM];

void cal_height(int *r, int n)
{
	int i, j, k = 0;
	rank[sa[0]] = 0;
	for (i = 1; i <= n; ++i) rank[sa[i]] = i;
	for (i = 0; i < n; height[rank[i++]] = k) {
		for (k?--k:0, j = sa[rank[i]-1]; r[j+k]==r[i+k]; ++k) ;
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
	// p 记得初始化
	for (l = 1, p = 0; p < n; m = p, l <<= 1) {
		for (p = 0, i = n-l; i < n; ++i) y[p++] = i;
		for (i = 0; i < n; ++i) {
			if (sa[i] >= l) 
				y[p++] = sa[i] - l;
		}
		for (i = 0; i < m; ++i) buc[i] = 0;
		for (i = 0; i < n; ++i) buc[ x[y[i]] ]++;
		for (i = 1; i < m; ++i) buc[i] += buc[i-1];
		for (i = n-1; i >= 0; --i) sa[ --buc[ x[y[i]] ] ] = y[i];
		for (t=x, x=y, y=t, x[sa[0]]=0, p=1, i=1; i < n; ++i) {
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
int lcp(int a, int b)  // LCP
{
	//a = rank[a], b = rank[a];
	if (a > b) swap(a, b);
	++a;
	int l = 0;
	for (; (1 << l) <= b-a+1; ++l) ;
	--l;
	return min(best[a][l], best[b-(1<<l)+1][l]);
}

int a[MAXM];
int s[MAXM];

int main()
{
	int n;
	while (EOF != scanf("%d", &n) && n != 0) {
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		for (int i = 1; i < n; ++i) s[i] = a[i] - a[i-1] + 88;

		s[n] = 0;
		suffix(s+1, n, 88*2+1);
		init_rmq(n-1);
		
		int l = 1, r = n, m;
		while (l < r) {
			m = l + (r - l) / 2 + 1;
			int i = 1;
			bool can = false;
			for (int j = i + 1; i < n; ++j) {
				if (lcp(i, j) >= m) {
				} else if (i + 1 == j) {
					i = j;
				} else {
					int Min = MAXM + MAXM, Max = -1;
					for (int k = i; k < j; ++k) {
						if (Min > sa[k]) Min = sa[k];
						if (Max < sa[k]) Max = sa[k];
					}
					if (Max - Min > m) {
						can = true;
						break;
					} else {
						i = j;
					}
				}
			}
			if (can) {
				l = m;
			} else {
				r = m - 1;
			}
		}
		printf("%d\n", l+1 >= 5 ? l+1 : 0);
	}
	return 0;
}


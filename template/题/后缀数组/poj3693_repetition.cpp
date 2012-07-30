#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXM = 100000 + 10;
const int LOG_MAXM = 18;

int sa[MAXM], rank[MAXM], height[MAXM];
int buc[MAXM], X[MAXM], Y[MAXM];
int r[MAXM];

void cal_height(int *r, int n)
{
	int i, j, k = 0;
	rank[sa[0]] = 0;
	for (i = 1; i <= n; ++i) rank[sa[i]] = i;
	for (i = 0; i < n; height[rank[i++]]=k) {
		for (k?k--:0, j = sa[rank[i]-1]; r[i+k]==r[j+k]; ++k) ;
	}
}

bool cmp(int *r, int a, int b, int l) 
{
	return r[a] == r[b] && r[a+l] == r[b+l];
}

void suffix(int *r, int n, int m)
{
	int i, l, p, *x = X, *y = Y, *t;
	for (i = 0; i < m; ++i) buc[i] = 0;
	for (i = 0; i < n; ++i) buc[ x[i]=r[i] ]++;
	for (i = 1; i < m; ++i) buc[i] += buc[i-1];
	for (i = n - 1; i >= 0; --i) sa[ --buc[x[i]] ] = i;
	// 注意p的初始化，虽然这题的代码不初始化p也过了，但是那是因为数据弱，数据有问题！！！
	for (l = 1, p = 1; p < n; m = p, l *= 2) {
		for (p = 0, i = n - l; i < n; ++i) y[p++] = i;
		for (i = 0; i < n; ++i) {
			if (sa[i] >= l) y[p++] = sa[i] - l;
		}
		for (i = 0; i < m; ++i) buc[i] = 0;
		for (i = 0; i < n; ++i) buc[ x[y[i]] ]++;
		for (i = 0; i < m; ++i) buc[i] += buc[i-1];
		for (i = n - 1; i >= 0; --i) sa[ --buc[ x[y[i]] ] ] = y[i];
		for (t=x, x=y, y=t, x[ sa[0] ] = 0, i = 1, p = 1; i < n; ++i) {
			x[sa[i]] = cmp(y, sa[i-1], sa[i], l) ? p-1 : p++;
		}
	}
	cal_height(r, n-1);
	/**
	printf("%7s ", "rank");
	for (int i = 0; i < n; ++i) printf("%d:%d, ", i, rank[i]);
	printf("\n%7s ", "sa");
	for (int i = 0; i < n; ++i) printf("%d:%d, ", i, sa[i]);
	printf("\n%7s ", "height");
	for (int i = 1; i < n; ++i) printf("%d:%d, ", i, height[i]);
	puts("");
	/* */
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
int lcp(int a, int b)
{
	a = rank[a], b = rank[b];
	if (a > b) swap(a, b);
	++a;
	int l;
	for (l = 0; (1 << l) <= b-a+1; ++l) ;
	--l;
	return min(best[a][l], best[b-(1<<l)+1][l]);
}

char str[MAXM];
int num[MAXM];
int ans[MAXM];

int main()
{
	int nCase = 0;
	while (EOF != scanf("%s", str) && str[0] != '#') {
		//puts(str);
		int n = 0;
		for (; str[n]; ++n) num[n] = str[n] - 'a' + 1;
		num[n] = 0;
		suffix(num, n+1, 28);
		init_rmq(n);

		int maxr = 0, a = 0;
		for (int l = 1; l < n; ++l) {
			for (int i = 0; i+l < n; i += l) {
				int k = lcp(i, i+l);
				int r = k / l  + 1;
				int t = i - (l - k % l);
				if (t >= 0 && k % l > 0) {
					if (lcp(t, t + l) >= k) ++r;
				}
				if (r > maxr) {
					a = 0;
					maxr = r;
					ans[a++] = l;
				} else if (r == maxr) {
					ans[a++] = l;
				}
			}
		}
		//printf("a:%d, maxr:%d\n", a, maxr);
		int start = -1, l;
		for (int i = 1; i <= n && start == -1; ++i) {
			for (int j = 0; j < a; ++j) {
				int tl = ans[j];
			//	printf("%d %d\n", sa[i], tl);
				if (lcp(sa[i], sa[i] + tl) >= (maxr-1)*tl) {
					start = sa[i];
					l = tl * maxr;
					break;
				}
			}
		}
		printf("Case %d: ", ++nCase);
		for (int i = 0; i < l; ++i)	putchar(str[start + i]);
		puts("");
	}
	return 0;
}


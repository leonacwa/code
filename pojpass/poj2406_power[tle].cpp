/* 后缀数组解法
 * 倍增算法超时，N*logN, 应该使用DC3
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int MAXM = 1000000 + 10;

int buc[MAXM];
int X[MAXM], Y[MAXM];
int rank[MAXM], sa[MAXM], height[MAXM];

void cal_height(int *r, int n)
{
	int i, j, k = 0;
	for (i = 1; i <= n; ++i) rank[sa[i]] = i;
	for (i = 0; i < n; height[rank[i++]] = k) {
		for (k?--k:0, j=sa[rank[i]-1]; r[j+k]==r[i+k]; ++k) ;
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

char str[MAXM];
int num[MAXM];

int main()
{
	while (EOF != scanf("%s", str) && str[0] != '.') {
		int n = 0;
		for (; str[n]; ++n) num[n] = str[n];
		num[n] = 0;
		suffix(num, n+1, 128);
		int k, h = height[rank[0]];
		for (k = 1; k <= n/2; ++k) {
			if (rank[0] < rank[k]) continue;
			if (n % k != 0) continue;
			h = min(h, height[rank[k]+1]);
			if (h == n - k) break;
		}
		if (k > n/2) k = n;
		printf("%d\n", n / k);
	}
	return 0;
}


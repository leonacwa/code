#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXM = 2 * 100000 + 100;

int rank[MAXM], sa[MAXM], height[MAXM];
int X[MAXM], Y[MAXM], buc[MAXM];

void cal_height(int *r, int n) {
	int i, j, k = 0;
	for (i = 1; i <= n; ++i) rank[sa[i]] = i;
	for (i = 0; i < n; height[rank[i++]]=k) {
		for (k?--k:0, j=sa[rank[i]-1]; r[j+k]==r[i+k]; ++k) ;
	}
}

bool cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a+l] == r[b+l];
}

void suffix(int *r, int n, int m) {
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
		for (t=x, x=y, y=t, x[sa[0]]=0,  i = 1, p = 1; i < n; ++i) {
			x[sa[i]] = cmp(y, sa[i-1], sa[i], l) ? p-1 : p++;
		}
	}
	cal_height(r, n-1);
}

char stra[MAXM], strb[MAXM];
int num[MAXM];

int main()
{
	while (EOF != scanf("%s%s", stra, strb)) {
		int la = 0, lb = 0, l = 0;
		for (la = 0; stra[la]; ++la) {
			num[l++] = stra[la] - 'a' + 1;
		}
		num[l++] = 27;
		for (lb = 0; strb[lb]; ++lb) {
			num[l++] = strb[lb] - 'a' + 1;
		}
		num[l] = 0;
		suffix(num, l+1, 28);
		int len = 0;
		for (int i = 2; i <= l; ++i) {
			if (sa[i-1] < la && la < sa[i] || sa[i] < la && la < sa[i-1]) {
				if (len < height[i]) len = height[i];
			}
		}
		printf("%d\n", len);
	}
	return 0;;
}


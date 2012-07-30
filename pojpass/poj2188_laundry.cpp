#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 1000 + 10;
int a[MAXN], b[MAXN], c[MAXN];

int tmp[MAXN];

int merge_sort(int *a, int n) 
{
	if (n <= 1) return 0;
	int ret = 0, mid = n / 2;
	int lx = mid, ly = n - mid, i;
	ret = merge_sort(a, lx) + merge_sort(a + lx, ly);
	int ix = 0, iy = 0, l = 0;
	while (ix < lx && iy < ly) {
		if (a[ix] < a[lx+iy]) {
			tmp[l++] = a[ix++];
		} else {
			tmp[l++] = a[lx + iy++];
			ret += lx - ix;
		}
	}
	while (ix < lx) tmp[l++] = a[ix++];
	while (iy < ly) tmp[l++] = a[lx+iy++];
	for (l = 0; l < n; ++l) {
		a[l] = tmp[l];
	}
	return ret;
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i], &b[i]);
		for (int i = 1; i <= n; ++i) {
			c[b[i]] = i;
		}
		for (int i = 1; i <= n; ++i) {
			a[i] = c[a[i]];
		}
		printf("%d\n", merge_sort(a+1, n));
	}
	return 0;
}


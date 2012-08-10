#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 100000 + 100;

int a[MAXN], b[MAXN], c[MAXN];
int hi[MAXN];
int f[MAXN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		for (int t, i = 0; i < n; ++i) {
			scanf("%d", &t);
			b[t] = i;
		}
		for (int i = 0; i < n; ++i) {
			c[i] = b[a[i]];
		}
		int len = 1;
		f[0] = 1;
		hi[1] = c[0];
		for (int i = 1; i < n; ++i) {
			int l = 1, r = len;
			while (l <= r) {
				int m = l + (r - l) / 2;
				if (hi[m] > c[i]) {
					l = m + 1;
				} else  {
					r = m - 1;
				}
			}
			hi[l] = c[i];
			f[i] = l;
			if (len < l) len = l;
		}
		printf("%d\n", len);
	}
	return 0;
}


#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <iostream>
using namespace std;
const int MAXN = 10005;
const int INT_MAX_2 = INT_MAX / 2;
int a[MAXN];
int f[2][MAXN];

int main()
{
	int n, l;
	while (EOF != scanf("%d %d", &n, &l)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		if (n == 1) {-
			puts("0");
			continue;
		}
		int d = l / (n - 1);
		int k = l % (n - 1);
		int cr = 0;
		for (int i = 0; i <= k; ++i) {
			f[cr][i] = INT_MAX_2;
		}
		f[cr][0] = a[0];
		for (int i = 1; i < n; ++i) {
			cr = 1 - cr;
			for (int j = 0; j <= k; ++j) f[cr][j] = INT_MAX_2;
			for (int j = 0; j <= k && j <= i; ++j) {
				int t = abs(a[i] - (j * (d + 1) + (i - j) * d));
				if (j > 0) {
					f[cr][j] = f[1-cr][j-1] + t;
				}
				f[cr][j] = min(f[cr][j], f[1-cr][j] + t);
				//printf("f[%d][%d] : %d\n", i, j, f[cr][j]);
			}
		}
		printf("%d\n", f[cr][k]);
	}
	return 0;
}


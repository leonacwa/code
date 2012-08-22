#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 1001;
typedef long long LLONG;
int n, l;
int c[NN];
LLONG f[NN][NN][2];

int main()
{
	while (EOF != scanf("%d %d", &n, &l)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", c+i);
		}
		sort(c, c+n);
		for (int i = 0; i < n; ++i) {
			f[i][i][0] = f[i][i][1] = abs(l - c[i]) * n;
		}
		for (int k = 1; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				int j = i + k;
				if (j >= n) break;
				int r = n - (j - i + 1) + 1;
				f[i][j][0] = min(f[i+1][j][0] + (c[i+1] - c[i]) * r, f[i+1][j][1] + (c[j] - c[i]) * r);
				f[i][j][1] = min(f[i][j-1][0] + (c[j] - c[i]) * r, f[i][j-1][1] + (c[j] - c[j-1]) * r);
			}
		}
		LLONG ans = min(f[0][n-1][0], f[0][n-1][1]);
		//printf("%lld\n", ans);
		printf("%I64d\n", ans);
	}
	return 0;
}


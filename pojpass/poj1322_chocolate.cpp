#include <stdio.h>
#include <string.h>
#include <math.h>
const double EPS = 1e-8;
int c, n, m;
double f[2][101];

double solve(int c, int n, int m)
{
	if (c < m || n < m || (n+m) % 2 == 1) return 0.0;
	memset(f, 0, sizeof(f));
	f[0][0] = 1.0;
	double pre = 1000.0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= i && j <= c; ++j) {
			if ((i + j) % 2 == 1) continue;
			f[i % 2][j] = 0.0;
			if (j+1 <= c) f[i % 2][j] += f[(i-1) % 2][j+1] * (j + 1.0) / c;
			if (j-1 >= 0) f[i % 2][j] += f[(i-1) % 2][j-1] * (c - j + 1.0) / c;
			if (j == m) {
				if (fabs(f[i % 2][j] - pre) < EPS) return pre;
				else pre = f[i % 2][j];
			}
		}
	}
	return f[n % 2][m];
}

int main()
{
	while (EOF != scanf("%d", &c) && c != 0) {
		scanf("%d %d", &n, &m);
		printf("%.3f\n", solve(c, n, m));
	}
	return 0;
}


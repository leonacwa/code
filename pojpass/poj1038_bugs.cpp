#include <stdio.h>
#include <string.h>
const int MM = 10;
const int NN = 155;
const int th[11] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};
int f[2][59049+10];
int bad[NN][MM];
int p[MM], q[MM];
int n, m, k;

inline int max(int a, int b)
{
	return a > b ? a : b;
}

int en_state(int as[])
{
	int ret = 0;
	for (int i = 0; i < m; ++i) {
		ret += as[i] * th[i];
	}
	return ret;
}

void de_state(int s, int as[])
{
	for (int i = 0; i < m; ++i) {
		as[i] = s % 3;
		s /= 3;
	}
}

void init()
{
	int s = 0;
	memset(f[0], -1, sizeof(f[0]));
	for (int i = 0; i < m; ++i) {
		s += (1 + bad[0][i]) * th[i];
	}
	f[0][s] = 0;
}

void dfs(int i, int j, int ct, int s1, int s2)
{
	f[i % 2][s2] = max(f[i % 2][s2], f[(i-1) % 2][s1]);
	if (j+2 < m && q[j] == 0 && q[j+1] == 0 && q[j+2] == 0) {
		int s3 = s2 + th[j] * 2 + th[j+1] * 2 + th[j+2] * 2;
		f[i % 2][s3] = max(f[i % 2][s3], ct+1);
		dfs(i, j+3, ct+1, s1, s3);
	}
	if (j+1 < m && q[j] == 0 && q[j+1] == 0 && p[j] == 0 && p[j+1] == 0) {
		int s3 = s2 + th[j] * 2 + th[j+1] * 2;
		f[i % 2][s3] = max(f[i % 2][s3], ct+1);
		dfs(i, j+2, ct+1, s1, s3);
	}
	if (j+1 < m) {
		dfs(i, j+1, ct, s1, s2);
	}
}

void dp()
{
	init();
	for (int i = 1; i < n; ++i) {
		memset(f[i % 2], -1, sizeof(f[i % 2]));
		for (int s = 0; s < th[m]; ++s) {
			if (f[(i-1) % 2][s] != -1) {
				de_state(s, p);
				for (int j = 0; j < m; ++j) {
					if (bad[i][j] == 1) {
						q[j] = 2;
					} else {
						q[j] = p[j] - 1;
						if (q[j] < 0) q[j] = 0;
					}
				}
				dfs(i, 0, f[(i-1) % 2][s], s, en_state(q));
			}
		}
	}
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d %d", &n, &m, &k);
		memset(bad, 0, sizeof(bad));
		for (int i = 0; i < k; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			x--, y--;
			bad[x][y] = 1;
		}
		dp();
		int ans = 0;
		for (int s = 0; s < th[m]; ++s) {
			if (f[(n-1) % 2][s] > ans) ans = f[(n-1) % 2][s];
		}
		printf("%d\n", ans);
	}
	return 0;
}


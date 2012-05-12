#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

long long f[201][2];
bool diff[1000000+5];
bool ma[201][201];
int at[201];
int n, m;

long long dp(int k, int pr, int s)
{
	if (f[k][s] != -1) return f[k][s];
	f[k][s] = s ? at[k] : 0;
	for (int i = 0; i < n; ++i) {
		if (ma[k][i] && pr != i) {
			if (s) {
				f[k][s] += dp(i, k, 0);
			} else {
				f[k][s] += max(dp(i, k, 1), dp(i, k, 0)); 
			}
		}
	}
	return f[k][s];
}

int main()
{
	while (EOF != scanf("%d %d", &n, &m) && n > 0 && m > 0) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &at[i]);
		}
		memset(diff, 0, sizeof(diff));
		for (int i = 0; i < m; ++i) {
			int p;
			scanf("%d", &p);
			diff[p] = true;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				if (diff[at[j] - at[i]]) {
					ma[i][j] = ma[j][i] = true;
				} else {
					ma[i][j] = ma[j][i] = false;
				}
			}
		}
		memset(f, -1, sizeof(f));
		printf("%lld\n", max(dp(0, -1, 1), dp(0, -1, 0)));
		//printf("%I64d\n", max(dp(0, -1, 1), dp(0, -1, 0)));
	}
	return 0;
}


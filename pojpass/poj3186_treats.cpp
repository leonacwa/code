#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 2005;
int n;
int a[NN];
int f[NN][NN];

int main()
{
	while (EOF != scanf("%d", &n)) {
		a[0] = a[n+1] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a+i);
		}
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= n; ++i) {
			f[i][0] = f[i-1][0] + a[i] * i;
			f[0][i] = f[0][i-1] + a[n-i+1] * i;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; i+j <= n; ++j) {
				f[i][j] = max(f[i-1][j] + a[i] * (i+j), f[i][j-1] + a[n-j+1]*(i+j));
			}
		}
		int ans = 0;
		for (int i = 0; i <= n; ++i) {
			if (ans < f[i][n-i]) {
				ans = f[i][n-i];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


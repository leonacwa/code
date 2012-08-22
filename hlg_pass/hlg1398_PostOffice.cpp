#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 1001;
typedef long long llong;

int pos[MAXN];
llong f[MAXN][MAXN];

int main()
{
	int n, q;
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &pos[i]);
		}
		for (int i = 1; i <= n; ++i) {
			f[i][i] = 0;
			for (int j = i + 1; j <= n; ++j) {
				int m1 = (j - 1 + i) / 2, m2 = (j + i) / 2;
				if (m1 == m2) {
					f[i][j] = f[i][j-1] + pos[j] - pos[m1];
				} else {
					f[i][j] = f[i][j-1] + pos[j] - pos[m2] + ((m1 - i + 1) - (j - 1 - m1)) * (pos[m2] - pos[m1]);
				}
			}
		}
		scanf("%d", &q);
		while (q--) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (a > b) {
				swap(a, b);
			}
			printf("%lld\n", f[a][b]);
		}
	}
	return 0;
}


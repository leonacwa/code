#include <cstdio>
#include <cstring>

typedef long long int64;
const int MAXN = 1000005;
const int64 INF64 = 0x7fffffffffffffffLL;

int n, c;
int64 f[MAXN];
int x[MAXN];

int64 F(int64 d) {
	int i = 1, j = 1;
	int64 t = 0, dx;
	while (j <= n+1) {
		if (j == n+1 || x[j] - x[i] > d) {
			dx = x[j-1] - x[i];
			t += dx * dx + c;
			i = j;
		}
		++j;
	}
	return t;
}

int main() {
	while (EOF != scanf("%d%d", &n, &c)) {
		if (n == 0 && c == 0) break;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &x[i]);
		}
		int64 l = 0, r = x[n];
		while (l < r) {
			int64 m1 = (2*l + r) / 3, m2 = (l + 2*r) / 3;
			if (F(m1) <= F(m2)) {
				r = m2;
			} else {
				l = m1+1;
			}
		}
		printf("%lld\n", F(l));
	}
	return 0;
}

/*hlg1496
 * NCPC2011 Inversions
 * */
#include <cstdio>
#include <cstring>

typedef long long int64;
const int MAXN = 100005;
int64 c[2][MAXN];

inline int lowbit(int x) {
	return x & (-x);
}

void add(int64 c[], int n, int i, int64 v) {
	for (; i <= n; i += lowbit(i)) c[i] += v;
}

int64 sum(int64 c[], int n, int i) {
	int64 s = 0;
	for (; i > 0; i -= lowbit(i)) s += c[i];
	return s;
}

int main() 
{
	int n, a;
	while (EOF != scanf("%d", &n)) {
		memset(c, 0, sizeof(c));
		int64 ans = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a);
			int64 t = sum(c[0], n, n) - sum(c[0], n, a);
			add(c[0], n, a, 1);
			if (t > 0) add(c[1], n, a, t);
			ans += sum(c[1], n, n) - sum(c[1], n, a);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

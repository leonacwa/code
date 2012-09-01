#include <cstdio>
#include <cstring>

typedef long long int64;
const int MAXN = 801;

int64 num[MAXN];
int tab[MAXN];
bool vis[MAXN];

int64 gcd(int64 x, int64 y) {
	if(!x||!y) return x > y ? x : y;
	for (int64 t; t = x % y; x = y, y = t);
	return y;
}

int64 multi(int64 a[], int64 n) //下标从零开始
{
	int64 c=a[0],i;
	for(i=1;i<n;i++)
		c = a[i] / gcd(a[i],c) * c;
	return c;
}

int main() {
	int n, k;
	while (EOF != scanf("%d%d", &n, &k)) {
		if (n == 0 && k == 0) break;

		int cnt = 0;
		memset(vis, 0, sizeof(vis));

		int start = n - (n-1) % k - 1;
		for (int i = 0; i < k; ++i) {
			int now = start + i;
			if (now >= n) now -= k;
			while (now >= 0) {
				tab[cnt++] = now;
				now -= k;
			}
		}

		cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			int now = i, count = 0;
			while (!vis[now]) {
				vis[now] = true;
				int nxt = tab[now];
				++count;
				now = nxt;
			}
			num[cnt++] = count;
		}
		int64 ans = multi(num, cnt);
		printf("%lld\n", ans);
	}
	return 0;
}


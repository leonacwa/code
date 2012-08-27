/* Cinema in Akiba
 * 树状数组
 * */
#include <cstdio>
#include <cstring>
const int MAXN = 50005;

int n, m, c[MAXN], tab[MAXN];
int lowbit(int x) {
	return x & (-x);
}
void add(int i, int v) {
	for (; i <= n; i += lowbit(i)) c[i] += v;
}

int sum(int i) {
	int s = 0;
	for (; i > 0; i -= lowbit(i)) s += c[i];
	return s;
}

int bin(int t) {
	int l = 1, r = n;
	while (l < r) {
		int m = (l + r) >> 1;
		if (sum(m) < t) {
			l = m + 1;
		} else {
			r = m;
		}
	}
	return l;
}

int main() {
	while (EOF != scanf("%d", &n)) {
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; ++i) add(i, 1);
		for (int i = 1, t; i <= n; ++i) {
			scanf("%d", &t);
			tab[i] = bin(t);
			add(tab[i], -1);
		}
		bool output = false;
		scanf("%d", &m);
		for (int i = 0, t; i < m; ++i) {
			scanf("%d", &t);
			if (output) printf(" ");
			else output = true;
			printf("%d", tab[t]);
		}
		puts("");
	}
	return 0;
}

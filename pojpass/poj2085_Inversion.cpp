/*
 * POJ 2085 Inversion
 * 构造法
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 50005;
int n;
int c[MAXN];
int lowbit(int i) {
	return i & -i;
}
void add(int i, int v) {
	for (; i < MAXN; i += lowbit(i)) c[i] += v;
}
int sum(int i) {
	int s = 0;
	for (; i > 0; i -= lowbit(i)) s += c[i];
	return s;
}

int find(int a) {
	int l = 1, r = n;
	while (l < r) {
		int m = (l + r) >> 1;
		if (a < sum(m)) {
			r = m;
		} else {
			l = m + 1;
		}
	}
	return l;
}

int main() {
	LL m;
	while (EOF != scanf("%d%lld", &n, &m) && n != -1 && m != -1) {
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; ++i) add(i, 1);
		for (LL i = n; i > 0; --i) {
			LL i2 = (i-1) * (i - 2) / 2;
			int a = max(0, int(m - i2)), p = find(a);
			if (i != n) putchar(' ');
			printf("%d", p);
			add(p, -1);
			m -= a;
		}
		putchar('\n');
	}
	return 0;
}

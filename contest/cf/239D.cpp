/*
 * CF 239 D. Boring Partition
 * 贪心。
 * 证明了只需判断最小的数和其他数分开还是在一起即可得到答案
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int v[MAXN], p[MAXN];

int main() {
	int n, h;
	scanf("%d%d", &n, &h);
	for (int i = 0; i < n; ++i) {
		scanf("%d", v+i);
		p[i] = v[i];
	}
	sort(v, v + n);
	int t1 = v[n-1] + v[n-2] - (v[0] + v[1]);
	int t2 = max(v[n-1] + v[n-2], v[0] + v[n-1] + h) - min(v[0] + v[1] + h, v[1] + v[2]);
	if (n == 2 || t1 <= t2) {
		printf("%d\n", t1);
		for (int i = 0; i < n-1; ++i) printf("1 ");
		puts("1");
	} else {
		printf("%d\n", t2);
		bool can = true;
		for (int i = 0; i < n; ++i) {
			if (i) putchar(' ');
			if (p[i] == v[0] && can) {
				putchar('1');
				can = false;
			} else {
				putchar('2');
			}
		}
		puts("");
	}
	return 0;
}

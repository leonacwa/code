#include <stdio.h>
#include <string.h>

const int NN = 100000 + 5;
struct Node {
	int h, l;
};
int n;
int h[NN];
int top;
Node st[NN];

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &h[i]);
		}
		h[n] = 0;
		top = 0;
		st[0].h = h[0];
		st[0].l = 0;
		long long ans = 0, tmp;
		for (int i = 1; i <= n; ++i) {
			if (st[top].h > h[i]) {
				while (top > -1 && st[top].h > h[i]) {
					tmp = (long long)st[top].h * (i - st[top].l);
					if (ans < tmp) ans = tmp;
					--top;
				}
				st[++top].h = h[i];
			} else {
				st[++top].h = h[i];
				st[top].l = i;
			}
		}
		//printf("%lld\n", ans);
		printf("%I64d\n", ans);
	}
	return 0;
}


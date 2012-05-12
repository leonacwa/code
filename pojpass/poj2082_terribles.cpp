#include <stdio.h>
const int NN = 50005;
struct Node {
	int h, l;
};
int n, top;
Node st[NN];
int h[NN], w[NN];
int sw[NN];

int main()
{
	while (EOF != scanf("%d", &n) && n != -1) {
		w[0] = h[0] = sw[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d", &w[i], &h[i]);
			sw[i] = sw[i-1] + w[i];
		}
		h[n+1] = -1;
		sw[n+1] = sw[n] + h[n+1];
		top = 0;
		st[0].h = h[1];
		st[0].l = 1;
		int ans = 0, tmp;
		for (int i = 2; i <= n+1; ++i) {
			if (top > -1 && st[top].h > h[i]) {
				while (top > -1 && st[top].h > h[i]) {
					tmp = st[top].h * (sw[i-1] - sw[st[top].l-1]);
					if (ans < tmp) ans = tmp;
					--top;
				}
				st[++top].h = h[i];
			} else {
				st[++top].h = h[i];
				st[top].l = i;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


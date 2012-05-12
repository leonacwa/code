#include <stdio.h>

struct Node {
	int e, i;
};
int n, top;
Node st[100005];
int e[100005];
long long sum[100005];

int main()
{
	while (EOF != scanf("%d", &n)) {
		sum[0] = 0;
		e[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &e[i]);
			sum[i] = sum[i-1] + e[i];
		}
		e[n+1] = -1;
		sum[n+1] = sum[n] + e[n+1];
		top = 0;
		st[0].e = e[1];
		st[0].i = 1;
		long long ans = -10000, tmp;
		int left, right;
		for (int i = 2; i <= n+1; ++i) {
			if (top > -1 && st[top].e > e[i]) {
				while (top > -1 && st[top].e > e[i]) {
					tmp = ((long long)st[top].e) * (sum[i-1] - sum[st[top].i-1]);
					if (ans < tmp) {
						ans = tmp;
						left = st[top].i;
						right = i - 1;
					}
					--top;
				}
				st[++top].e = e[i];
			} else {
				st[++top].e = e[i];
				st[top].i = i;
			}
		}
		printf("%lld\n", ans);
		//printf("%I64d\n", ans);
		printf("%d %d\n", left, right);
	}
	return 0;
}


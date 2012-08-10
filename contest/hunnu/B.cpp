#include <stdio.h>

struct Node {
	int p, next;
};
Node ar[1001];
int n;
int x[1001];
int ans[1001];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &x[i]);
			ar[i].p = i;
			ar[i].next = (i + 1) % n;
		}
		int cur = n - 1, pre;
		for (int cnt = 1; cnt <= n; ++cnt) {
			for (int i = 0; i < cnt; ++i) {
				pre = cur;
				cur = ar[cur].next;
			}
			ans[ar[cur].p] = x[cnt-1];
			ar[pre].next = ar[cur].next;
		}
		for (int i = 0; i < n - 1; ++i) {
			printf("%d ", ans[i]);
		}
		printf("%d\n", ans[n-1]);
	}
	return 0;
}


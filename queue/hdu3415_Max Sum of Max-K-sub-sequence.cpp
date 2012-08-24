/* HDOJ 3415 Max Sum of Max-K-sub-sequence
 * 单调队列的应用
 * WA了好多次，没仔细想好啊
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 200005;
int a[MAXN], sum[MAXN];
int q[MAXN];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, k;
		scanf("%d%d", &n, &k);
		sum[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			sum[i] = a[i] + sum[i-1];
		}
		for (int i = n+1; i <= n+n; ++i) sum[i] = a[i - n] + sum[i-1];
		int fr = 0, ta = 1, ans = sum[1], s = 1, t = 1;
		q[0] = 0;
		for (int i = 1, v; i <= n + n; ++i) {
			while (fr < ta && q[fr] < i-k) ++fr;
			if (q[fr] >= n) break;
			v = sum[i] - sum[q[fr]];
			if (ans < v) {
				ans = v, s = q[fr]+1, t = i;
			}
			while (fr < ta && sum[q[ta-1]] > sum[i]) --ta; 
			q[ta++] = i;
		}
		printf("%d %d %d\n", ans, s, (t-1) % n + 1);
	}
	return 0;
}

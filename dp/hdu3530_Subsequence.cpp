/* HDU 3530 Subsequence
 * 单调队列优化 DP
 * 维护一个递减的最大值队列，递增的最小值队列。
 * 如果最大值和最小值的差超过上界，那么只能减小最大值或者增大最小值，并修改起始位置
 * 如果最大值的和最小值的差低于下界，那么只能再读入一个数，希望能增大最大值或减小最小值，使得差大于等于下界
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int a[MAXN];
int q1[MAXN], q2[MAXN];

int main() {
	int n, low, up;
	while (EOF != scanf("%d%d%d", &n, &low, &up)) {
		int ans = 0, h1 = 0, t1 = 0, h2 = 0, t2 = 0, b = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			while (h1 < t1 && a[q1[t1-1]] < a[i]) --t1;
			q1[t1++] = i;
			while (h2 < t2 && a[q2[t2-1]] > a[i]) --t2;
			q2[t2++] = i;
			while (a[q1[h1]] - a[q2[h2]] > up) {
				if (q1[h1] < q2[h2]) {
					b = q1[h1] + 1;
					++h1;
				} else {
					b = q2[h2] + 1;
					++h2;
				}
			}
			int t = a[q1[h1]] - a[q2[h2]];
			if (low <= t && t <= up) {
				t = i - b + 1;
				if (ans < t) ans = t;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

/* Wizarding Duel
 * */
#include <cstdio>
#include <algorithm>
using namespace std;

int a[55];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		sort(a, a + n);
		int ans = 0, sum = n*(n-1)/2; // sum总共有多少胜利
		for (int i = n-1; i >= 0; --i) {
			int tmax = sum - i*(i-1)/2; // ith最多能胜利的次数,不会出现调整使得有人的胜利次数超过n-1
			if (tmax < a[i]) { // 减小胜利次数
				ans += a[i] - tmax;
				a[i] = tmax;
			}
			sum -= a[i]; // 剩余胜利次数
		}
		ans += sum;
		printf("%d\n", ans);
	}
	return 0;
}

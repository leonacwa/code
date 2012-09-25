/* HDU 4415 Assassin’s Creed
 * 贪心 
 * 如果能砍掉一个b不为0的，则所有b不为0的均能砍死，且不影响最优解。
 * 但是不能用匕首杀b不为0的，可能用来杀一些b=0的会得到更优的解。
 * 那么，当能砍死一个人的时候，并且获得匕首数量少于n-1时，则应该用耐久度去砍死耐久度最低的几个人，使得砍死的人尽量多，并且已经能用匕首砍死一些人，人数为匕首数量
 *  */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Kill {
	int a, b;
	bool operator < (const Kill &B) const {
		return a < B.a;
	}
};
Kill p[100005];

int main() {
	int runs;
	scanf("%d", &runs);
	for (int ca = 1; ca <= runs; ++ca) {
		int n, m, ansn = 0, ansm = 0;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &p[i].a, &p[i].b);
			ansn += p[i].b;
		}
		sort(p, p+n);
		int k = -1;
		for (int i = 0; i < n; ++i) {
			if (p[i].a <= m && p[i].b > 0) {
				k = i;
				ansm = p[k].a;
				break;
			}
		}
		if (k != -1 && ansn >= n) {
			ansn = n;
		} else {
			if (k == -1) ansn = 0;
			else ++ansn;
			for (int i = 0; i < n; ++i) {
				if (k != i && ansm + p[i].a <= m && ansn < n) {
					ansm += p[i].a;
					++ansn;
				}
			}
		}
		printf("Case %d: %d %d\n", ca, ansn, ansm);
	}
	return 0;
}

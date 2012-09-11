/* HDU 4268 Alice and Bob
 * 贪心，用multiset快速查找
 * */
#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
typedef multiset<int> MSI;

const int MAXN = 100005;

PII a[MAXN], b[MAXN];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d%d", &a[i].first, &a[i].second);
		for (int i = 0; i < n; ++i) scanf("%d%d", &b[i].first, &b[i].second);
		sort(a, a + n);
		sort(b, b + n);
		int ans = 0;
		int p = 0;
		MSI ms;
		for (int i = 0; i < n; ++i) {
			while (p < n && b[p].first <= a[i].first) {
				ms.insert(b[p].second);
				++p;
			}
			if (ms.size() > 0) {
				MSI::iterator it = ms.lower_bound(a[i].second);
				if (it == ms.end()) --it;
				while (it != ms.begin() && *it > a[i].second) --it;
				if (*it <= a[i].second) {
					++ans;
					ms.erase(*it);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

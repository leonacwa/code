/* POJ 3017 Cut the Sequence
 * 单调队列减少决策数量
 * */
#include <cstdio>
#include <string>
#include <set>
using namespace std;

typedef long long int64;

const int MAXN = 100005;

int64 a[MAXN];
int64 f[MAXN];
int d[MAXN];
int q[MAXN];

template <class T>
void check_min(T &a, const T b) {
	if (a > b) a = b;
}

int main() {
	int n;
	int64 m;
	while (EOF != scanf("%d%lld", &n, &m)) {
		a[0] = 0;
		bool can = true;
		for (int i = 1, t; i <= n; ++i) {
			scanf("%d", &t);
			a[i] = t;
			if (t > m) can = false;
		}
		if (!can) {
			puts("-1");
			continue;
		}
		int fr = 0, re = 0, low = 0;
		f[0] = 0;
		int64 sum = 0;
		for (int i = 1; i <= n; ++i) {
			sum += a[i];
			while (sum > m) {
				sum -= a[++low];
			}
			while (fr < re && q[fr] < low) {
				++fr;
			}
			while (fr < re && a[q[re-1]] <= a[i]) {
				--re;
			}
			if (fr < re) {
				d[re] = q[re-1];
			} else {
				d[re] = low;
			}
			q[re++] = i;
			if (d[fr] < low) {
				d[fr] = low;
			}
			f[i] = f[d[fr]] + a[q[fr]];
			for (int j = fr + 1; j < re; ++j) {
				check_min(f[i], f[d[j]] + a[q[j]]);
			}
		}
		printf("%lld\n", f[n]);
	}
	return 0;
}

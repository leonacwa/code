#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;
const int NN = 100000 + 2;
typedef long long LLONG;
int n;
int a[NN];
LLONG f1, f2;
LLONG m1[NN], m2[NN];

int main()
{
	while (~scanf("%d", &n) && n > 0) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		f1 = 0;
		f2 = 0;
		m1[0] = m2[n+1] = -LLONG_MAX;
		for (int i = 1; i <= n; ++i) {
			if (f1 <= 0) {
				f1 = a[i];
			} else {
				f1 = f1 + a[i];
			}
			m1[i] = max(m1[i-1], f1);
			int ni = n - i + 1;
			if (f2 <= 0) {
				f2 = a[ni];
			} else {
				f2 = f2 + a[ni];
			}
			m2[ni] = max(m2[ni+1], f2);
		}
		LLONG ans = -LLONG_MAX;
		for (int i = 1; i < n; ++i) {
			int t = m1[i] + m2[i+1];
			if (ans < t) {
				ans = t;
			}
		}
		printf("%lld\n", ans);
		//printf("%I64d\n", ans); // windows
	}
	return 0;
}


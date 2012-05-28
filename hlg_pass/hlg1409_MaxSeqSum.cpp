#include <cstdio>
#include <cstring>
#include <climits>
#include <climits>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

typedef long long llong;
typedef multiset<int> MSI;
typedef multiset<int>::iterator MSIIT;
typedef multiset<int>::reverse_iterator MSIRIT;

const int MAXN = 100000 + 10;
int a[MAXN];
llong ABS(llong x) { return x < 0 ? -x : x; }

llong solve(int a[], int n, int l, int k)
{
	MSI A, B;
	llong now = 0, ret = -LLONG_MAX;
	for (int i = 0; i < n; ++i) {
		if (i - l >= 0) {
			if (a[i - l] >= 0) {
				now -= a[i - l];
			} else {
				MSIIT it;
				if ((it = B.find(a[i - l])) != B.end()) {
					now -= *it;
					B.erase(it);
				} else if ((it = A.find(-a[i - l])) != A.end()) {
					A.erase(it);
					now -= -a[i - l];
					while (A.size() < k && B.size() > 0) {
						it = B.begin();
						A.insert(- *it);
						now -= (*it) * 2;
						B.erase(it);
						
					}
				} else {
				}
			}
		}
		if (a[i] >= 0) {
			now += a[i];
		} else {
			if (k == 0) {
				B.insert(a[i]);
				now += a[i];
			} else if (A.size() < k) {
				A.insert(-a[i]);
				now += -a[i];
			} else {
				MSIIT it = A.begin();
				if (*it < -a[i]) {
					now -= (*it) * 2;
					now += -a[i];
					B.insert(- *it);
					A.insert(-a[i]);
					A.erase(it);
					
				} else {
					B.insert(a[i]);
					now += a[i];
				}
			}
		}
		if (l-1 <= i && ret < ABS(now)) {
			ret = ABS(now);
		}
	}
	return ret;
}

int main()
{
	int n, l, k;
	while (EOF != scanf("%d %d", &n, &l)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		scanf("%d", &k);
		llong a1 = solve(a, n, l, k);
		for (int i = 0; i < n; ++i) {
			a[i] = -a[i];
		}
		llong a2 = solve(a, n, l, k);
		printf("%lld\n", max(a1, a2));
	}
	return 0;
}


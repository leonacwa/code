/*
 * CF 252 B. Unsorting Array
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long LL;

const int MAXN = 100005;

int a[MAXN];

LL C2(LL n) {
	if (n & 1) return (n - 1) / 2 * n;
	return n / 2 * ( n - 1);
}

int main() {
	int n, d;
	while (cin >> n >> d) {
		for (int i = 0; i < n; ++i) cin >> a[i];
		int l = 0, r = 0;
		LL ans = 0;
		while (l <= r && l < n) {
			if (r+1 < n && a[r+1] - a[l] <= d) {
				r++;
			} else {
				//cout << ":" << l << " " << r << " " << C2(r - l) << endl;
				ans += C2(r - l);
				l++;
				if (r < l) r = l;
			}
		}
		cout << ans << endl;;
	}
	return 0;
}

/*
 * CF 237 C. Primes on Interval
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = int(1e6) + 1;
bool is[MAXN];

void init_prm() {
	memset(is, 1, sizeof(is));
	is[0] = is[1] = 0;
	for (int i = 2; i < MAXN; ++i) {
		if (is[i]) {
			for (int j = i + i; j < MAXN; j += i) is[j] = 0;
		}
	}
}

bool check(int a, int b, int k, int l) {
	int cnt = 0, i;
	for (i = a; i < a+l && i <= b; ++i) {
		if (is[i]) ++cnt;
	}
	if (cnt < k) return false;
	while (i <= b) {
		if (is[i-l]) --cnt;
		if (is[i]) ++cnt;
		++i;
		if (cnt < k) return false;
	}
	return cnt >= k;
}

int main() {
	init_prm();
	int a, b, k;
	while (cin >> a >> b >> k) {
		if (!check(a, b, k, b - a + 1)) cout << "-1" << endl;
		else {
			int l = 1, r = b - a + 1;
			while (l < r) {
				int m = (l + r) / 2;
				if (check(a, b, k, m)) r = m;
				else l = m + 1;
			}
			cout << l << endl;
		}
	}
	return 0;
}

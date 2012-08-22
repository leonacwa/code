#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	long long N, s1, s2, v1, v2, ans;
	int nTest;
	scanf("%d", &nTest);
	for (int nCase = 1; nCase <= nTest; ++nCase) {
		scanf("%lld %lld %lld %lld %lld", &N, &s1, &v1, &s2, &v2);
		if (s1 > s2) {
			swap(s1, s2);
			swap(v1, v2);
		}
		ans = 0;
		if (s2 > 100000) {
			for (int i = 0; i * s2 <= N; ++i) {
				long long res = (N - i * s2) / s1 * v1 + i * v2;
				if (ans < res) ans = res;
			}
		} else {
			if (v1 * s2 > v2 * s1) {
				swap(s1, s2);
				swap(v1, v2);
			}
			for (int i = 0; i < s2 && i * s1 <= N; ++i) {
				long long res = i * v1 + (N - i * s1) / s2 * v2;
				if (ans < res) ans = res;
			}
		}
		printf("Case #%d: %lld\n", nCase, ans);
	}
	return 0;
}


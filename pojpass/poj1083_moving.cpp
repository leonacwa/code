#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 201;
int s[MAXN], t[MAXN];
int cnt[MAXN];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &s[i], &t[i]);
			if (s[i] > t[i]) {
				swap(s[i], t[i]);
			}
			s[i] = (s[i] + (s[i] & 1)) / 2;
			t[i] = (t[i] + (t[i] & 1)) / 2;
		}
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			for (int j = s[i]; j <= t[i]; ++j) {
				++cnt[j];
			}
		}
		int ans = 0;
		for (int i = 0; i < MAXN; ++i) {
			if (ans < cnt[i]) {
				ans = cnt[i];
			}
		}
		printf("%d\n", ans * 10);
	}
	return 0;
}


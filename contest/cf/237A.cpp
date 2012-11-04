#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int cnt[1445];

int main() {
	memset(cnt, 0, sizeof(cnt));
	int n, h, m;
	while (cin >> n) {
		for (int i = 0; i < n; ++i) {
			cin >> h >> m;
			++cnt[h * 60 + m];
		}
		int ans = 0;
		for (int i = 0; i <= 1440; ++i) {
			if (ans < cnt[i]) ans = cnt[i];
		}
		cout << ans << endl;
	}
	return 0;
}

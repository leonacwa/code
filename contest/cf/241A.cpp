/* CF 241 A.Old Peykan
 * */
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1005;

int d[MAXN];
int s[MAXN];

int main() {
	int m, k;
	while (cin >> m >> k) {
		for (int i = 0; i < m; ++i) {
			cin >> d[i];
		}
		for (int i = 0; i < m; ++i) {
			cin >> s[i];
		}
		int res = 0, ms = 0, ans = 0;
		for (int i = 0; i < m; ++i) {
			res += s[i];
			if (ms < s[i]) ms = s[i];
			if (d[i] > res) {
				int t = int(ceil(((double)d[i]-res)/ms));
				ans += t * k;
				res += t * ms;
			}
			ans += d[i];
			res -= d[i];
		}
		cout << ans << endl;
	}
	return 0;
}

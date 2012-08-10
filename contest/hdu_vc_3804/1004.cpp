/* Trouble
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int64_t s[5][205];
int64_t res[200*200 + 100];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%lld", &s[i][j]);
				//scanf("%I64d", &s[i][j]);
			}
		}
		int tot = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				res[tot++] = (-(s[0][i] + s[1][j]));
			}
		}
		sort(res, res + tot);
		int t = 0;
		for (int i = 1; i < tot; ++i) {
			if (res[t] != res[i]) res[++t] = res[i];
		}
		tot = t + 1;
		bool ans = false;
		for (int i = 0; i < n && !ans; ++i) {
			for (int j = 0; j < n && !ans ; ++j) {
				int64_t t2 = s[2][i] + s[3][j];
				for (int k = 0; k < n && !ans; ++k) {
					if (binary_search(res, res + tot, t2 + s[4][k])) {
						ans = true;
						break;
					}
				}
			}
		}
		puts(ans ? "Yes" : "No");
	}
	return 0;
}

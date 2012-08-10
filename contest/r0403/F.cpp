#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

int f[10], ct[10], oct[10];
char s[10000+5];
char ts[10000+5];
char ans[10000+5];

int main()
{
int oct[10];
	int nTest;
	int n, k;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d", &n, &k);
		scanf("%s", s);
		int ls = strlen(s);
		memset(f, 0, sizeof(f));
		memset(ct, 0, sizeof(ct));
		for (char *ps = s; *ps; ++ps) {
			ct[*ps - '0']++;
		}
		for (int i = 0; i <= 9; ++i) {
			oct[i] = ct[i];
		}
		int output = 0;
		for (int i = 0; i <= 9; ++i) {
			if (ct[i] >= k) {
				printf("%d\n%s\n", 0, s);
				output = 1;
				break;
			}
		}
		if (output) continue;
		for (int dt = 1; dt <= 9; ++dt) {
			for (char c = '0'; c <= '9'; ++c) {
				for (char *ps = s; *ps; ++ps) {
					int fee = abs(*ps - c);
					if (fee == dt && ct[c - '0'] < k) {
						f[c - '0'] += fee;
						ct[c - '0']++;
					}
					if (ct[c -'0'] >= k) break;
				}
			}
		}
		int minFee = INT_MAX;
		for (int i = 0; i <= 9; ++i) {
			minFee = min(minFee, f[i]);
		}
		ans[0] = 0;
		for (int i = 0; i <= 9; ++i) {
			if (minFee != f[i]) continue;
			strcpy(ts, s);
			for (int dt = 1; dt <= 9; ++dt) {
				for (int j = 0; j < ls; ++j) {
					if (oct[i] < k && ts[j] - '0' - i == dt) {
						ts[j] = '0' + i;
						oct[i]++;
					}
					if (oct[i] >= k) break;
				}
				for (int j = ls-1; j >= 0; --j) {
					if (oct[i] < k && ts[j] - '0' - i == -dt) {
						ts[j] = '0' + i;
						oct[i]++;
					}
					if (oct[i] >= k) break;
				}
			}
			if (ans[0] == 0 || strcmp(ans, ts) > 0) {
				strcpy(ans, ts);
			}
		}
		printf("%d\n%s\n", minFee, ans);
	}
	return 0;
}


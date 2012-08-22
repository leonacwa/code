#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

const int NN = 101;
const int S = 100000;
int n;
int s, f;
int dp[S*2 + 10];

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = -S; i <= S; ++i) {
			dp[S + i] = -INT_MAX;
		}
		dp[S] = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &s, &f);
			if (s >= 0) {
				for (int j = S; j >= -S+s; --j) {
					if (dp[S+j-s] > -INT_MAX ) {
						dp[S+j] = max(dp[S+j], dp[S+j-s] + f);
					}
				}
			} else {
				for (int j = -S; j <= S+s; ++j) {
					if (dp[S+j-s] > -INT_MAX) {
						dp[S+j] = max(dp[S+j], dp[S+j-s] + f);
					}
				}
			}
		}
		int ans = 0;
		for (int j = 0; j <= S; ++j) {
			if (dp[S+j] >= 0) {
				ans = max(ans, j + dp[S+j]);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


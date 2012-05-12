#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int NN = 5000+5;
int dp[2][NN];
char s[NN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		scanf("%s", s+1);
		memset(dp, 0, sizeof(dp));
		for (int i = n; i > 0; --i) {
			for (int j = i; j <= n; ++j) {
				if (s[i] == s[j]) {
					dp[i % 2][j] = dp[(i+1) % 2][j-1];
				} else {
					dp[i % 2][j] = min(dp[(i+1) % 2][j], dp[i % 2][j-1]) + 1;
				}
			}
		}
		printf("%d\n", dp[1][n]);
	}
	return 0;
}


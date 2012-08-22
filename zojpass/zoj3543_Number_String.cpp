/* zoj 3543 Number String
我的水平太次了
DP 方程，方程难看懂，关键是理解组合排列。
*/
#include <stdio.h>
#include <string.h>
#define MAXN 1002
#define MOD 1000000007

char s[MAXN+2];
int dp[MAXN][MAXN];

int main()
{
    int i, j, k, n, sum;
    while (scanf("%s", s+2) == 1) {
        dp[1][1] = 1;
        n = strlen(s+2) + 1;
        for (i = 2; i <= n; i++) {
            if (s[i] == '?') {
                sum = 0;
                for (j = 1; j < i; ++j) sum = (sum + dp[i-1][j]) % MOD;
                for (j = 1; j <= i; j++) {
                    dp[i][j] = sum;
                }
            }
            if (s[i] == 'I') {
                dp[i][1] = 0;
                for (j = 2; j <= i; ++j) {
                    dp[i][j] = (dp[i][j-1] + dp[i-1][j-1]) % MOD;
                }
            }
            if (s[i] == 'D') {
                dp[i][i] = 0;
                for (j = i-1; j >= 1; --j) {
                    dp[i][j] = (dp[i][j+1] + dp[i-1][j]) % MOD;
                }
            }
        }
        sum = 0;
        for (i = 1; i <= n; i++) sum = (sum + dp[n][i]) % MOD;
        printf("%d\n", sum);
    }
    return 0;
}

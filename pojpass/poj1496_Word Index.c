/* poj 1496 Word Index */
#include <stdio.h>
int dp[27][6], sum[6];
int main()
{
    int i, j, sl, ans;
    char str[11];

    for (j = 0; j < 26; j++) {
        dp[j][1] = 1;
    }
    for (i = 2; i <= 5; i++) {
        for (j = 26 - i; j >= 0; j--) {
            dp[j][i] += dp[j+1][i];
            dp[j][i] += dp[j+1][i-1];
        }
    }
    for (i = 1; i <= 5; i++) {
        for (j = 0; j < 26; j++) {
            sum[i] += dp[j][i];
        }
    }
    while (gets(str)) {
        ans = 0;
        for (i = 0; ans != -1 && str[i+1]; i++) {
            if (str[i] >= str[i+1]) {
                ans = -1;
                break;
            }
        }
        if (ans != -1) {
            for (sl = 0; str[sl]; sl++) {
                ans += sum[sl];
            }
            for (j = 0, i = sl; i > 0; i--) {
                for ( ; j < str[sl-i]-'a'; j++) {
                    ans += dp[j][i];
                }
                j++;
            }
        }
        printf("%d\n", ans+1);
    }
    return 0;
}

// ÐÞÂ·
#include <stdio.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX (((unsigned int)~0)>>1)
#endif

int seg[301], sum[301];
int dp[2][301];

int min(int a, int b){return a<b?a:b;}
int max(int a, int b){return a>b?a:b;}

int main()
{
    int tt, i, j, k, n, m, total, k1, k2;
    scanf("%d", &tt);
    seg[0] = 0;
    while (tt--){
        scanf("%d %d", &m, &n); // seg m, team n;
        sum[0] = 0;
        for (i = 1; i <= m; i++) {
            scanf("%d", &seg[i]);
            sum[i] = sum[i-1] + seg[i];
        }
        
        dp[1][0] = 0;
        for (i = 1; i <= m; i++){
            dp[1][i] = dp[1][i-1] + seg[i];
        }
        k2 = 1;
        for (i = 2; i <= n; i++){
            k1 = k2;
            k2 = 1 - k1;
            
            memset(dp[k2], 0x7f, sizeof(dp[k2]));
            dp[k2][0] = 0;
            
            for (j = m-n+i; j >= i; j--){
                total = j - i + 1;
                for (k = 1; k <= total; k++){
                    dp[k2][j] = min(dp[k2][j], max(dp[k1][j-k], sum[j]-sum[j-k]));
                }
            }
        }
        printf("%d\n", dp[n%2][m]);
    }
    return 0;
}

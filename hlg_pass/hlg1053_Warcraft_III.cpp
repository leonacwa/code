#include <stdio.h>
#include <string.h>
#define MAXG 99999

int dp[MAXG];

int main()
{
    int t, g, u, i, j, a, c, tt;
    scanf("%d", &t);
    while (t--){
        scanf("%d%d", &g, &u);
        memset(dp, 0, sizeof(int)*MAXG);
        for (i = 0; i < u; i++){
            scanf("%d%d", &a, &c);
            for (j = c; j <= g; j++){
                if (dp[j] < (tt=dp[j-c]+a))
                    dp[j] = tt;
            }
        }
        printf("%d\n", dp[g]);
    }
    return 0;
}

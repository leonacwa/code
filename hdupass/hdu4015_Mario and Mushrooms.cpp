/*Mario and Mushrooms*/
#include <stdio.h>
int main()
{
    int cs, tt, m, k;
    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) { /* 概率算法原理不明*/
        scanf("%d %d", &m, &k);
        printf("Case #%d: %0.8lf\n", cs, 1.0/(m*k+1+k));
    }
    return 0;
}

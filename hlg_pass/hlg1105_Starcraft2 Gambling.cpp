/// Starcraft2 Gambling   http://acm.hrbust.edu.cn/showproblem.php?problemid=1105
#include <stdio.h>

int main()
{
    int tt;
    double a, b, c, cn;
    scanf("%d", &tt);
    while (tt--){
        scanf("%lf %lf %lf", &a, &b, &c);
        cn = 999999999;
        if ( (cn / a + 1) + (cn / b + 1) + (cn / c + 1) <= cn  )
            printf("JiaoZhuV5!\n");
        else
            printf("Orz!\n");
    }
    return 0;
}

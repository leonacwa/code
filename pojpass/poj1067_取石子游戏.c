/* poj 1067 取石子游戏 */
#include <stdio.h>
#include <math.h>
int main()
{
    double _sqrt5 = sqrt(5.0);
    int a, b, k, ak, bk, ak_1, bk_1;
    while (2 == scanf("%d %d", &a, &b)) {
        if (a > b) {
            k = a; a = b; b = k;
            /* a = a ^ b; b = a ^ b; a = a ^ b; */
            /* a ^= b; b ^= a;a ^= b; */
        }
        k = (int)(a*2/(1+_sqrt5));
        ak = (int)(k*(1+_sqrt5)/2);
        bk = ak + k;
        ak_1 = (int)((k+1)*(1+_sqrt5)/2);
        bk_1 = ak_1 + k+1;
        printf("%d\n", !((a == ak_1 && b == bk_1) || (a == ak && b == bk)));
    }
    return 0;
}

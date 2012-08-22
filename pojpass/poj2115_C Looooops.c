/* poj 2115 C Looooops */
#include <stdio.h>

__int64 Ex_EUCLID(__int64 a, __int64 b, __int64 *x, __int64 *y)
{
    __int64 d;
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    d = Ex_EUCLID(b, a%b, y, x);
    *y = *y - (a/b)*(*x);
    return d;
}
int main()
{
    __int64 a, b, c, k, bb, d, _2k, x, y, xx, ld;
    while (4==scanf("%I64d %I64d %I64d %I64d", &a, &b, &c, &k) && (a|b|c|k)) {
        _2k = 1LL << k;
        bb = b - a;
        d = Ex_EUCLID(c, _2k, &x, &y);
        if (bb % d) {
            puts("FOREVER");
        }
        else {
            xx = x * (bb/d);
            ld = _2k / d;
            xx = (ld + xx%ld) % ld;
            printf("%I64d\n", xx);
        }
    }
    return 0;
}

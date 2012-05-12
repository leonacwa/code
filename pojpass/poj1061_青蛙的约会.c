/** poj 1061 青蛙的约会 */
#include <stdio.h>
typedef long long llong;
llong Ex_EUCLID(llong a, llong b, llong *x, llong *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    llong gcd = Ex_EUCLID(b, a%b, y, x);
    *y = *y - (a/b)*(*x);
    return gcd;
}
int main()
{
    llong x, y, m, n, L, x_, y_, b, d, ld, a;
    scanf("%I64d%I64d%I64d%I64d%I64d", &x, &y, &m, &n, &L);
    if (n > m) {
        a = n - m;
        b = x - y;
    }
    else {
        a = m - n;
        b = y - x;
    }
    d = Ex_EUCLID(a, L, &x_, &y_);
    if (b % d) {
        printf("Impossible\n");
    }
    else {
        x_ = x_*(b/d);
        /** x是原方程的一个解，通解： (x + i*(L/d)) % L，答案取的是最小整数解 */
        ld = L / d;
        x_ = (ld + x_%ld) % ld; // x 和 x_搞乱让我白白WA
        printf("%I64d\n", x_);
    }
    return 0;
}

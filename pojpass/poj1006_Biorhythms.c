/* poj 1006 Biorhythms */
/// 中国剩余定理
#include <stdio.h>
int Ex_EUCLID(int a, int b, int *x, int *y)
{
    if (b == 0) {
        *x = a;
        *y = 0;
        return a;
    }
    int gcd = Ex_EUCLID(b, a%b, y, x);
    *y = *y - (a/b)* (*x);
    return gcd;
}
int get_C(int m, int n) /// ax _= 1 (mod n), return x, a is m
{
    int d, x, y;
    d = Ex_EUCLID(m, n, &x, &y); /// d should be 1
    x = (x+n) %n; //x = (x*(1/d) + n) % n;
    return m * x;
}
int main()
{
    int p, e, i, d, a, x = 0;
    int c[3];
    c[0] = get_C(28*33, 23);
    c[1] = get_C(23*33, 28);
    c[2] = get_C(23*28, 33);
    //printf("%d %d %d\n", c[0], c[1], c[2]);

    while (4 == scanf("%d %d %d %d", &p, &e, &i, &d)) {
        if (p == -1 && e == -1 && i == -1 && d == -1) {
            break;
        }
        a = (p*c[0] +
             e*c[1] +
             i*c[2] - d + (23*28*33) - 1) % (23*28*33) + 1;
        printf("Case %d: the next triple peak occurs in %d days.\n", ++x, a);
    }
    return 0;
}

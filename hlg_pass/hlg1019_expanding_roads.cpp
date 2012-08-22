/* Expanding Rods */
#include <stdio.h>
#include <math.h>
const double PI = 3.14159265;
const double eps = 1e-12;

int main()
{
    double L, n, C;
    while (EOF != scanf("%lf %lf %lf", &L, &n, &C) && L >= 0 && n >= 0 && C >= 0) {
        if (L == 0 || n == 0 || C ==0) {
            printf("0.000\n");
            continue;
        }
        double L1 = (1+n*C)*L;
        double la = 0, ra = 2*PI, ma;
        while (ra - la >= eps) {
            ma = (ra - la)/2 + la;
            if (L1 < L*ma/(2*sin(ma/2))) {
                ra = ma;
            } else {
                la = ma;
            }
        }
//        printf("%.3lf\n", L*(1-cos(ma/2)) / (2*sin(ma/2)));
        printf("%.3lf\n", L1/ma * (1-cos(ma/2)));
    }
    return 0;
}
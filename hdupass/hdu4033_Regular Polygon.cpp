/*Regular Polygon*/
#include <stdio.h>
#include <math.h>
#define eps 1e-10
#define MAXN 101
#define PI 3.14159265

double a[MAXN];
int n;

int to2PI(double c)
{
    int i;
    double a1, a2, res = 0;
    for (i = 0; i < n; i++) {
        a1 = a[i];
        a2 = a[(i+1)%n];
        if (a1+a2 < c+eps) return 1;
        if (fabs(a1-a2)+eps > c) return -1;
        res += acos( (a1*a1+a2*a2-c*c) /(2*a1*a2));
    }
    if (fabs(res-2*PI) < eps) return 0;
    if (res+eps < 2*PI) return -1;
    return 1;
}

double can(double l, double r)
{
    double mid;
    int ret;
    while (l+eps < r) {
        mid = (r+l) / 2;
        //printf("Maybe %0.3lf %0.3lf %0.3lf\n", l, mid, r);
        ret = to2PI(mid);
        if (ret == 0) return mid;
        if (ret > 0) r = mid;
        else l = mid;
    }
    mid = (r+l) / 2;
    ret = to2PI(mid);
    if (ret == 0) return mid;
    return -1;
}

int main()
{
    int tt, cs;
    scanf("%d", &tt);
    int i;
    double r;
    for (cs = 1; cs <= tt; cs++) {
        scanf("%d", &n);
        r = 0;
        for (i = 0; i < n; i++)  {
            scanf("%lf", &a[i]);
            if (r < a[i]) r = a[i];
        }
        r = can(0, r*2);
        if (r > 0) printf("Case %d: %0.3lf\n", cs, r);
        else printf("Case %d: impossible\n", cs);
    }
    return 0;
}

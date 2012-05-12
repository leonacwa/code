/* poj 1031 Fence */
#include <stdio.h>
#include <math.h>
#define MAXN 101
#define eps (1e-10)
#define PI 3.14159265

double fmin(double a, double b)
{   return a<b?a:b; }
double fmax(double a, double b)
{   return a>b?a:b; }
double det(double x1, double y1, double x2, double y2)/*叉积*/
{   return x1 * y2 - x2 * y1; }

void swap(double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

double angle(double x, double y) /*弧度*/
{
    double tmp;
    if (fabs(x) < eps) {
        if (y > 0) return PI / 2;
        else  return 3*PI/2;
    }
    else {
        tmp = atan(y / x); /* -pi/2 ~ +pi/2 atan2(y,x):-pi ~ + pi */
        if (x < 0)   tmp += PI;
        if (tmp < 0) tmp += 2*PI;
        return tmp;
    }
}

void get_angle_ab(double x1, double y1, double x2, double y2, double *a, double *b)
{
    if (det(x1, y1, x2, y2) < 0) {
        swap(&x1, &x2);
        swap(&y1, &y2);
    }
    *a = angle(x1, y1);
    *b = angle(x2, y2);
    if (*b < *a) *b += 2*PI;
}
int between(double a, double x, double b)
{
    return a-eps < x && x < b+eps;
}
int main()  /* atan(tangent)   k*h* */
{
    double k, h, x[MAXN], y[MAXN], a, b, aa, bb;
    int N, i, j;
    scanf("%lf %lf %d", &k, &h, &N);
    for (i = 0; i < N; i++) scanf("%lf %lf", &x[i], &y[i]);
    x[N] = x[0];
    y[N] = y[0];
    get_angle_ab(x[0], y[0], x[1], y[1], &a, &b);
    for (i = 1; i < N; i++) {
        get_angle_ab(x[i], y[i], x[i+1], y[i+1], &aa, &bb);
        for (j = -1; j <= 1; j++) {
            if (between(a, aa+j*2*PI, b) || between(a, bb+j*2*PI, b)) {
                a = fmin(a, aa+j*2*PI);
                b = fmax(b, bb+j*2*PI);
                break;
            }
        }
    }
    printf("%.2lf\n", k*h*fmin(b-a, 2*PI));
    return 0;
}

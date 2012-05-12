/*poj 1034 The dog task */
#include <stdio.h>
#include <string.h>
#include <math.h>
#define eps 1e-10
#define MAXN 100
int x[MAXN], y[MAXN], xm[MAXN], ym[MAXN], n, m, go[MAXN];
char v[MAXN];

double dist(int x1, int y1, int x2, int y2)
{
    double x = x1 - x2, y = y1 - y2;
    return sqrt(x*x + y*y);
}

int can(int i, int j)
{
    return dist(x[i], y[i], xm[j], ym[j]) + dist(xm[j], ym[j], x[i+1], y[i+1])
          < eps + 2*dist(x[i], y[i], x[i+1], y[i+1]);
}
int run(int i)
{
    int j;
    if (v[i]) return 0;
    v[i] = 1;
    for (j = 0; j < n-1; j++) {
        if (can(j, i) && (go[j]==-1 || run(go[j]))) {
            go[j] = i;
            return 1;
        }
    }
    return 0;
}
int main()
{
    int i, cnt;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++)  scanf("%d %d", &x[i], &y[i]);
    for (i = 0; i < m; i++)  scanf("%d %d", &xm[i], &ym[i]);
    cnt = n;
    memset(go, -1, sizeof(go));
    for (i = 0; i < m; i++) {
        memset(v, 0, sizeof(v));
        if (run(i))  cnt++;
    }
    printf("%d\n", cnt);
    for (i = 0; i < n; i++) {
        printf("%d %d ", x[i], y[i]);
        if (go[i] >= 0) printf("%d %d ", xm[go[i]], ym[go[i]]);
    }
    return 0;
}

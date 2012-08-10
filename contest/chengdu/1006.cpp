/*Rolling Hongshu*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define eps 1e-8
#define MAXN (1000+10)

struct Ball{
    int x, v, w;
    double h;
};

Ball b[MAXN];

bool cmpx(const Ball&a, const Ball&b)
{
    return a.x < b.x;
}
double vg(double h)
{
    return sqrt(h/40);
}

int main()
{
    int cs, tt;
    double iv, cv, vt, h, dh;
    int i, j, N, M, w;
    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        scanf("%d %d %d", &N, &M, &w);
        for (i = 0; i < N; i++) {
            scanf("%d %f", &b[i].x, &b[i].h);
            b[i].v = -1;
            b[i].w = -1;
        }
        for (i = 0; i < M; i++) {
            scanf("%d %d %d", &b[N+i], &b[N+i].v, &b[N+i].w);
            b[N+i].x = b[0].x + b[N+i].x;
        }
        for (i = N; i < N+M; i++) {
            for (j = 0; j < N-1; j++) {
                if (b[j].x == b[i].x)  b[i].h = b[j].h;
                else if (b[j+1].x == b[i].x)  b[i+1].h = b[j].h;
                else if (b[j].x < b[i].x && b[i].x < b[j+1].x) {
                    b[i].h = b[j].h * (b[j+1].x-b[i].x) / (b[j+1].x - b[j].x);
                }
            }
        }
        sort(b, b+N+M, cmpx);
        iv = cv = 0;
        h = b[0].h;
        for (i = 1; i < N+M-1; i++) {
            dh = b[i].h - h;
            if (dh > 0 && cv-(vt=vg(dh))+eps < 0) {
                cv += vt;
                iv + vt;
            } else if (dh < 0) {
                cv += vg(-dh);
            }
            if (b[i].v > 0) {
                if (cv < b[i].v) {
                    iv += b[i].v - cv;
                    cv = b[i].v;
                }
            }
            h = b[i].h;
            printf(" %0.2f  %0.2lf\n", cv, iv);
        }
        printf("Case %d: %0.2f\n", cs, iv);
    }
    return 0;
}

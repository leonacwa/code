/*  poj 1459 Power Network
  题意：痛苦的理解过程，写那么多就是废话。
  给几个发电站，给几个消耗站，再给几个转发点。
  发电站只发电，消耗站只消耗电，转发点只是转发电，再给各个传送线的传电能力。
  问你消耗站能获得的最多电是多少。
*/
/** 压入与重标记最大流算法 */
#include <stdio.h>
#include <string.h>
#define MAXN 128
#define bzero(x, size) memset(x, 0, size)
int c[MAXN][MAXN];
int n, np, nc, m;
int s, t;
int h[MAXN], e[MAXN];

int min(int a, int b) {return a<b?a:b;}

void init_preflow()
{
    int u;
    bzero(h, sizeof(h));
    bzero(e, sizeof(e));
    h[s] = n+2;
    for (u = 0; u <= t; u++) if (s != u && c[s][u] > 0) {
        e[u] = c[s][u];
        e[s] -= c[s][u];
        c[u][s] += c[s][u];
        c[s][u] = 0;
    }
}
int push(int u, int v)/// e[u]>0 && c[u][v]>0 && h[u]==h[v]+1
{
    int delta;
    delta = min(e[u], c[u][v]);
    e[u] -= delta;
    e[v] += delta;
    c[u][v] -= delta;
    c[v][u] += delta;
    return delta;
}

int relabel(int u)/// s!=u && t!=u && h[u]<=h[v] && c[u][v]>0 for all (u, v) int edges
{
    int v, cnt = 0, lcnt = 0, minh = 2*t-1;
    for (v = 0; v <= t; v++) {
        if (c[u][v] > 0) {
            cnt++;
            if (h[u] <= h[v]) {
                lcnt++;
                minh = min(minh, h[v]);
            }
        }
    }
    if (cnt && cnt == lcnt) {
        h[u] = minh + 1;
        return u;
    }
    //printf("%d != %d\n", cnt, lcnt);
    return -1;
}

int maxflow() /// 关键是高度h函数控制水流流向
{
    int u, v, flag;
    init_preflow();
    do {
        flag = 0;
        for (u = 0; u < n; u++) if (e[u] > 0) {
            if (-1 != relabel(u))
                flag = 1;
            for (v = 0; v <= t; v++) if (c[u][v] > 0 && h[u] == h[v]+1) {
                push(u, v);
                flag = 1;
            }
        }
    } while (flag);
    return e[t];
}
int main()
{
    int i, u, v, z;
    while (4 == scanf("%d %d %d %d", &n, &np, &nc, &m)){
        bzero(c, sizeof(c));
        s = n;
        t = n+1;
        for (i = 0; i < m; i++){ //
            while (getchar() != '(') {
            }
            scanf("%d,%d)%d", &u, &v, &z);
            c[u][v] = z;
        }
        for (i = 0; i < np; i++){ // power
            while (getchar() != '(') {
            }
            scanf("%d)%d", &u, &z);
            c[s][u] = z;
        }
        for (i = 0; i < nc; i++){ // consumer
            while (getchar() != '(') {
            }
            scanf("%d)%d", &u, &z);
            c[u][t] = z;
        }
        printf("%d\n", maxflow());
    }
    return 0;
}

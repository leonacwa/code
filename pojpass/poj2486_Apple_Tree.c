/* poj 2486 Apple Tree*/
#include <stdio.h>
#include <string.h>
#define MAXN (100+10)
#define MAXK (200+10)
typedef struct _Edge{
    int v, next;
}Edge;
Edge ve[MAXN*2];
int vs;
int g[MAXN], a[MAXN], vis[MAXN];
int n, k;
int bk[MAXN][MAXK], go[MAXN][MAXK]; /// 步数中含返回出发点的步数
int tmp_go[MAXK], tmp_bk[MAXK];

int max(int a, int b){return a>b?a:b;}

void push_edge(int a, int b)
{
    ve[vs].v = b;
    ve[vs].next = g[a];
    g[a] = vs++;
    ve[vs].v = a;
    ve[vs].next = g[b];
    g[b] = vs++;
}

void dp(int x, int y) /// 200*200/2 = 20000
{
    int i, j;
    memset(tmp_go, 0, sizeof(tmp_go));
    memset(tmp_bk, 0, sizeof(tmp_bk));
    for (i = 0; i <= k; i++) {
        for (j = 0; j <= i; j++) {
            tmp_go[i] = max(tmp_go[i],
                           max(bk[x][j] + go[y][i-j], bk[y][j] + go[x][i-j]));
            tmp_bk[i] = max(tmp_bk[i], bk[x][j] + bk[y][i-j]);
        }
    }
    for (i = 0; i <= k; i++) {
        go[x][i] = tmp_go[i];
        bk[x][i] = tmp_bk[i];
    }
}

void search(int x, int fa) /// < O(20000 * 200*200 = 800000000 = 八亿)
{
    int v, y, i;
    vis[x] = 1;
    for (v = g[x]; v != -1; v = ve[v].next) if ((y=ve[v].v) != fa && !vis[y]){
        search(y, x); /// y 作为起始点
        /// 返回到x
        for (i = k; i >= 2; i--) {
            bk[y][i] = bk[y][i-2] + a[y];
        }
        for (i = k; i >= 1; i--) {
            go[y][i] = go[y][i-1] + a[y];
        }
        dp(x, y);
    }
}

int main()
{
    int i, A, B;
    while (2 == scanf("%d %d", &n, &k)) {
        memset(g, -1, sizeof(g));
        memset(ve, -1, sizeof(ve));
        memset(vis, 0, sizeof(vis));
        memset(bk, 0, sizeof(bk));
        memset(go, 0, sizeof(go));
        for (i = 0; i < n; i++) {
            scanf("%d", a+i);
        }
        vs = 0;
        for (i = 1; i < n; i++) {
            scanf("%d %d", &A, &B);
            push_edge(A-1, B-1);
        }
        search(0, 0);
        printf("%d\n", go[0][k] + a[0]);
    }
    return 0;
}

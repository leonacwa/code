/* poj 2486 Apple Tree*/
#include <stdio.h>
#include <string.h>
#define MAXN (100+1)
#define MAXK (200+1)
typedef struct _Edge{
    int v, next;
}Edge;
Edge ve[MAXN*2];
int vs;
int g[MAXN], a[MAXN];
int n, k;
int bk[MAXN][MAXK], go[MAXN][MAXK];
int tmp_go[MAXK], tmp_bk[MAXK];

int max(int a, int b){ return a>b?a:b;}

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
            if (i-j >= 1) {
                tmp_go[i] = max(tmp_go[i], bk[x][j] + go[y][i-j-1]);
            }
            else {
                tmp_go[i] = max(tmp_go[i], go[y][i-j-1]);
            }
            if (j >= 2) {
                tmp_go[i] = max(tmp_go[i], bk[y][j-2] + go[x][i-j]);
            }
            else {
                tmp_go[i] = max(tmp_go[i], go[x][i-j]);
            }
            if (i-j >= 2) {
                tmp_bk[i] = max(tmp_bk[i], bk[x][j] + bk[y][i-j-2]);
            }
            else {
                tmp_bk[i] = max(tmp_bk[i], bk[x][j]);
            }
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
    for (v = g[x]; v != -1; v = ve[v].next) if ((y=ve[v].v) != fa){
        search(y, x);
        dp(x, y);
    }
    for (i = 0; i <= k; i++) {
        bk[x][i] += a[x];
        go[x][i] += a[x];
    }
}

int main()
{
    int i, A, B;
    while (2 == scanf("%d %d", &n, &k)) {
        memset(g, -1, sizeof(g));
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
        printf("%d\n", go[0][k]);
    }
    return 0;
}

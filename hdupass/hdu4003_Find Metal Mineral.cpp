/* Find Metal Mineral */
#include <stdio.h>
#include <string.h>

#define MAXN (10000+128)
#define MAXK 11

typedef long long llong;

struct Edge{
    int v, w, next;
};
Edge e[MAXN*2];
int e_cnt;
int first[MAXN];

llong dp[MAXN][MAXK];
int n, s, k;

void push_edge(int u, int v, int w)
{
    e[e_cnt].v = v;
    e[e_cnt].w = w;
    e[e_cnt].next = first[u];
    first[u] = e_cnt++;
    e[e_cnt].v = u;
    e[e_cnt].w = w;
    e[e_cnt].next = first[v];
    first[v] = e_cnt++;
}

void dfs(int u, int parent)
{
    int i, j, v, ii;
    for (i = first[u]; i != -1; i = e[i].next) {
        v = e[i].v;
        if (v == parent) continue;
        dfs(v, u);
    }

    for (i = first[u]; i != -1; i = e[i].next) {
        v = e[i].v;
        if (v == parent) continue;
        for (j = k; j >= 0; j--) {
            dp[u][j] += dp[v][0] + 2*e[i].w;
            for (ii = 1; ii <= j; ii++) {
                if (dp[u][j] > dp[u][j-ii]+dp[v][ii]+ii*e[i].w) {
                    dp[u][j] = dp[u][j-ii]+dp[v][ii]+ii*e[i].w;
                }
            }
        }
    }
}

int main()
{
    int i, n, u, v, w;
    while (~scanf("%d %d %d", &n, &s, &k)) {
        e_cnt = 0;
        memset(first, -1, sizeof(first));
        for (i = 1; i < n; i++) {
            scanf("%d %d %d", &u, &v, &w);
            push_edge(u, v, w);
        }
        memset(dp, 0, sizeof(dp));
        dfs(s, -1);
        printf("%I64d\n", dp[s][k]);
    }
    return 0;
}

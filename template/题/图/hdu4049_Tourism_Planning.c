/* Tourism Planning
 * 2011 ACM/ICPC 北京赛区网络赛
 * 最大权闭合图，转化成最大流解决，答案 = 所有节点权为正的值 - 最大流
 *
 * 注意：用邻接表的时候估计好边的数量。
*/

#include <stdio.h>
#include <string.h>

#define N 10
#define M 10
#define MAX_V (1100+2)
#define OO 0x0fffffff

struct Edge {
    int v, f, next;
};

struct Edge eg[MAX_V*4];

int eg_cnt;
int g[MAX_V];
int dist[MAX_V], Q[MAX_V];

int cost[M], v[N][M], b[N][N];
int n, m, src, dest;

int min(int a, int b) {return a<b?a:b;}

void init()
{
    src = n*m+n*n*m;
    dest = n*m+n*n*m+1;
    eg_cnt = 0;
    memset(g, -1, sizeof(g));
}

void add_edge(int u, int v, int c1, int c2)
{
    eg[eg_cnt].v = v;
    eg[eg_cnt].f = c1;
    eg[eg_cnt].next = g[u];
    g[u] = eg_cnt++;
    eg[eg_cnt].v = u;
    eg[eg_cnt].f = c2;
    eg[eg_cnt].next = g[v];
    g[v] = eg_cnt++;
}

int dinic_bfs() // find shortest path
{
    int i, u, v, l=0, r=0;
    memset(dist, -1, sizeof(dist));
    dist[Q[r++]=src] = 0;
    for (l = 0; l < r; l++) {
        for (i = g[u=Q[l]]; ~i; i = eg[i].next) {
            if (eg[i].f > 0 && dist[v=eg[i].v] < 0) {
                dist[Q[r++]=v] = dist[u] + 1;
                if (v == dest) return 1;
            }
        }
    }
    return 0;
}

int dinic_dfs(int u, int delta) // find delta
{
    if (u == dest) return delta;
    int i, v, tmp;
    for (i = g[u]; ~i; i = eg[i].next) {
        if (eg[i].f > 0 && dist[u] + 1 == dist[v=eg[i].v] &&
            (tmp=dinic_dfs(v, min(delta, eg[i].f))) > 0 ) {
                eg[i].f -= tmp;
                eg[i^1].f += tmp;
                return tmp;
        }
    }
    return 0;
}

int max_flow()
{
    int flow = 0, delta;
    while (dinic_bfs()) {
        while (delta = dinic_dfs(src, OO)) flow += delta;
    }
    return flow;
}

int main()
{
    int i, j, k, sum;
    while (2==scanf("%d %d", &n, &m) && (n+m)) {
        init();
        sum = 0;
        for (i = 0; i < m; i++) { // place
            scanf("%d", &cost[i]);
        }
        for (i = 0; i < n; i++) { // people -> place
            for (j = 0; j < m; j++) {
                scanf("%d", &v[i][j]);
                v[i][j] -= cost[j];
            }
        }
        for (i = 0; i < n; i++) { // people <-> people
            for (j = 0; j < n; j++) {
                scanf("%d", &b[i][j]);
            }
        }
        /* n*m nodes*/
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (v[i][j] > 0) {
                    sum += v[i][j];
                    add_edge(src, i*m+j, v[i][j], 0);
                }
                else add_edge(i*m+j, dest, -v[i][j], 0);
                if (j > 0)  add_edge(i*m+j, i*m+j-1, OO, 0);
            }
        }
        /* n*n*m nodes */
        for (i = 0; i < n; i++) {
            for (j = i+1; j < n; j++) {
                for (k = 0; k < m; k++) {
                    sum += b[i][j];
                    add_edge(src, n*m+(i*n+j)*m+k, b[i][j], 0);
                    add_edge(n*m+(i*n+j)*m+k, i*m+k, OO, 0);
                    add_edge(n*m+(i*n+j)*m+k, j*m+k, OO, 0);
                }
            }
        }
        sum = sum - max_flow();
        if (sum > 0) printf("%d\n", sum);
        else printf("STAY HOME\n");
    }
    //printf("OO:%d\n", OO);
    return 0;
}

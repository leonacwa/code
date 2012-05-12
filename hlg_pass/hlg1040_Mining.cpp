// Mining
#include <stdio.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX 0x7fffffff
#endif

#define MAX_STREET (150000+1)
#define MAX_JUNCTION (10000+1)

struct Link{
   int v, l, next;
} E[MAX_STREET*4];

int Es;
int d[3][MAX_JUNCTION];
char vis[MAX_JUNCTION];
int g[MAX_JUNCTION];
int J, B, C, N, S;

int dijkstra(int *d, int src)
{
    int i, u, p, t, min_dis;
    
    for (i = 0; i <= J; i++){
        d[i] = INT_MAX;
        vis[i] = 0;
    }
    d[src] = 0;
    u = src;
    while (u != -1){
         vis[u] = 1;
         for (p = g[u]; p != -1; p = E[p].next){
             if ((t=d[u] + E[p].l) < d[E[p].v])
                 d[E[p].v] = t;
         }
         u = -1;
         min_dis = INT_MAX;
         for (i = 1; i <= J; i++){
             if (!vis[i] && min_dis > d[i]){
                 min_dis = d[i];
                 u = i;
             }
         }         
    }
    return 0;
}
int main()
{
    int tt;
    int i, u, v, l, max_dis, Zfy, Kevin;
    
    scanf("%d", &tt);
    while (tt--){
        scanf("%d %d %d %d %d", &J, &B, &C, &N, &S);
        memset(g, -1, sizeof(g)); /** Junction  */

        Es = 0; /** read graphic , Street */
        for (i = 0; i < S; i++){
            scanf("%d %d %d", &u, &v, &l);
            E[Es].v = v;
            E[Es].l = l;
            E[Es].next = g[u];
            g[u] = Es;
            Es++;
            E[Es].v = u;
            E[Es].l = l;
            E[Es].next = g[v];
            g[v] = Es;
            Es++;
        }
        dijkstra(d[0], B);
        dijkstra(d[1], C);
        dijkstra(d[2], N);
        
        max_dis = -1;
        Zfy = -1;
        Kevin = -1;
        for (i = 1; i <= J; i++){
            if (max_dis <= d[0][i]){
                if (d[0][i]< INT_MAX && d[1][i] < INT_MAX && d[2][i] < INT_MAX)
                if (d[0][i]+d[1][i] == d[0][C] && d[0][i]+d[2][i] == d[0][N]
                    )//&& d[1][i] && d[2][i])
                {
                    max_dis = d[0][i];
                    Zfy = d[1][i];
                    Kevin = d[2][i];
                }
            }
        }
        printf("%d %d %d\n", max_dis, Zfy, Kevin);
    }
    return 0;
}

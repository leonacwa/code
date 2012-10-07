#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

/* Ford-Fulkerson算法
 * 邻接矩阵
 * 容易超时，慎重
 * */

const int MAXN = 205;
const int INF = INT_MAX / 2;

int c[MAXN][MAXN], pre[MAXN], q[MAXN];
int f[MAXN][MAXN];

#define inf 1000000000

int max_flow(int n, int mat[][MAXN], int source, int sink, int flow[][MAXN])
{
    int pre[MAXN], que[MAXN], d[MAXN], p, q, t, i, j;
    if (source == sink) return inf;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; flow[i][j++] = 0);
    for (;;)
    {
        for (i = 0; i < n; pre[i++] = 0);
        pre[t=source] = source + 1, d[t] = inf;
        for (p = q = 0; p <= q && !pre[sink]; t = que[p++])
            for (i = 0; i < n; i++)
                if (!pre[i] && (j = mat[t][i] - flow[t][i]))
                    pre[que[q++] = i] = t + 1, d[i] = d[t] < j ? d[t] : j;
                else if (!pre[i] && (j = flow[i][t]))
                    pre[que[q++] = i] = -t - 1, d[i] = d[t] < j ? d[t] : j;
        if (!pre[sink]) break;
        for (i = sink; i != source;)
            if (pre[i] > 0)
                flow[pre[i] - 1][i] += d[sink], i = pre[i] - 1;
            else
                flow[i][-pre[i] - 1] -= d[sink], i = -pre[i] - 1;
    }
    for (j = i = 0; i < n; j += flow[source][i++]);
    return j;
}

int main()
{
    int m, n;
    while (EOF != scanf("%d%d", &m, &n))
    {
        memset(c, 0, sizeof(c));
        for (int i = 0; i < m; ++i)
        {
            int a, b, f;
            scanf("%d%d%d", &a, &b, &f);
            c[a-1][b-1] += f;
        }
        int ans = max_flow(n, c, 0, n - 1, f);
        printf("%d\n", ans);
    }
    return 0;
}


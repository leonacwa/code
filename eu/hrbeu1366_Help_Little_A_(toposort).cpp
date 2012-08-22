// hrbeu 1366 Help Little A
/*
  问了一位学长，就过了，主要是拓扑排序，我最后处理的是枚举最优值
*/

#include <stdio.h>
#include <string.h>

const int maxn = 128;

bool g[maxn+1][maxn+1];
int dis[maxn+1];
int in[maxn+1];
int time[maxn+1];
int n, m;

int toposort()
{
    int q[maxn+1];
    int h = 0;
    int maxtime = 0, t = 0, sum = 0;
    int total = 0;
    for (int i = 1; i <= n; i++)
        dis[i] = time[i];
    
    while (total < n){
        maxtime = 0;
        h = 0;
        for (int j = 1; j <= n; j++){
            if (in[j] == 0){
                in[j] = -1;
                q[++h] = j;
                if (maxtime < time[j]){
                    maxtime = time[j];
                }
            }
        }
        if (h == 0 && total < n)
            return -1;
        total += h;
        for (int j = 1; j <= h; j++){
            for (int k = 1; k <= n; k++){
                if (in[k] > 0 && g[q[j]][k]){
                    if (dis[k] < dis[q[j]] + time[k])
                        dis[k] = dis[q[j]] + time[k];
                    --in[k];
                }
            }
        }
    }
    sum = 0;
    for (int i = 1; i <= n; i++)
        if (sum < dis[i])
            sum = dis[i];
    return sum;
}

int main()
{
    int sum;
    
    while (2 == scanf("%d %d", &n, &m)){
        for (int i = 1; i <= n; i++){
            scanf("%d", time+i);
        }
        memset(g, 0, sizeof(bool)*(maxn+1)*(maxn+1));
        memset(in, 0, sizeof(int)*(maxn+1));
        memset(dis, 0, sizeof(int)*(maxn+1));
        for (int i = 1, a, b; i <= m; i++){
            scanf("%d %d", &a, &b);
            if (!g[a][b]){
                g[a][b] = true;
                in[b]++;
            }
        }
        sum = toposort();
        if (sum > 0){
            printf("%d\n", sum);
        }
        else{
            printf("What a cup!\n");
        }
    }
    return 0;
}

/// Bombs of HRBUST http://acm.hrbust.edu.cn/showproblem.php?problemid=1101
#include <stdio.h>
#include <string.h>

int map[100][100];
int d[100];
char vis[100];

int main()
{
    int tt, i, j, v, k, min, n, ans;
    scanf("%d", &tt);
    while (tt--){
        scanf("%d", &n);
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                scanf("%d", &map[i][j]);
            }
        }
        memset(vis, 0, sizeof(vis));
        memset(d, 0x3f, sizeof(d));
        v = 0;
        d[0] = 0;
        ans = 0;
        while (v != -1){
            ans += d[v];
            vis[v] = 1;
            k = -1;
            min = 0x7fffffff;
            for (i = 0; i < n; i++) if (!vis[i]){
                if (d[i] > map[v][i])
                    d[i] = map[v][i];
                if (d[i] < min){
                    min = d[i];
                    k = i;
                }
            }
            v = k;
        }
        printf("%d\n", ans);
    }
    return 0;
}

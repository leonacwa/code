/* poj 1036 Gangsters */
#include <stdio.h>
#include <string.h>
#define MAXN 100
#define MAXK 100
typedef struct _Gan{
    int t, s, p;
}Gan;
Gan g[MAXN+1];
int sum[MAXN+1][MAXK+1];
int N, T, K;

int min(int a, int b) {  return a<b?a:b; }
int max(int a, int b) {  return a>b?a:b; }

int main()
{
    int s, s1, s2, i, j, k, t, dt;
    scanf("%d %d %d", &N, &K, &T);
    for (i = 1;i <= N; i++)  scanf("%d", &g[i].t);
    for (i = 1;i <= N; i++)  scanf("%d", &g[i].p);
    for (i = 1;i <= N; i++)  scanf("%d", &g[i].s);
    for (i = 1; i < N; i++) {
        k = i;
        for (j = i+1; j <= N; j++)  if (g[k].t > g[j].t) k = j;
        if (k != i) {
            g[0] = g[k];
            g[k] = g[i];
            g[i] = g[0];
        }
    }
    memset(sum, -1, sizeof(sum));
    sum[0][0] = 0;
    t = 0;
    for (i = 1; i <= N; i++) {
        dt = g[i].t - t;
        for (s1 = 0; s1 <= K; s1++) {
            k = min(K, s1 + dt);
            for (s2 = max(0, s1-dt); s2 <= k; s2++) {
                if (sum[i-1][s2] >= 0) {
                    s = sum[i-1][s2];
                    if (s1 == g[i].s) s += g[i].p;
                    if (sum[i][s1] < s)  sum[i][s1] = s;
                }
            }
        }
        t = g[i].t;
    }
    s = 0;
    for (i = 1; i <= N; i++) {
        for (s1 = 0; s1 <= K; s1++) {
            if (s < sum[i][s1]) s = sum[i][s1];
        }
    }
    printf("%d\n", s);
    return 0;
}

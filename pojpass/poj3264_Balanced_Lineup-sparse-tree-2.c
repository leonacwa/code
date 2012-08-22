/* poj 3264 Balanced Lineup */
/// Sparse Tree , RMQ
#include <stdio.h>
#define MAXN (50000 + 1)
#define INF (1000000 + 9999)

int h_max[MAXN][20], h_min[MAXN][20];  /// f[i][j], [i, i + 2^j - 1], f[i][0] = [i, i]
int n;

int max(int a, int b) {return a>b?a:b;}
int min(int a, int b) {return a<b?a:b;}

int main()
{
    int i, q, a, b, h, m;
    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; i++) {
        scanf("%d", &h);
        h_max[i][0] = h_min[i][0] = h;
    }
    for (m = 1; (1<<m)<=n+1; m++) {
        for (i = 1; i +(1<<m)-1 <= n; i++) {
            h_max[i][m] = max(h_max[i][m-1], h_max[i+(1<<(m-1))][m-1]);
            h_min[i][m] = min(h_min[i][m-1], h_min[i+(1<<(m-1))][m-1]);
        }
    }
    while (q--) {
        scanf("%d %d", &a, &b);
        for (m = 0; (1<<(m+1)) <= (b-a+1);m++ ){
        }
        printf("%d\n", max(h_max[a][m], h_max[b-(1<<m)+1][m]) -
               min(h_min[a][m], h_min[b-(1<<m)+1][m]));
    }
    return 0;
}

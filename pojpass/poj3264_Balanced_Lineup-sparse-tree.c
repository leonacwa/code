/* poj 3264 Balanced Lineup */
/// Sparse Tree , RMQ
#include <stdio.h>
#define MAXN (50000 + 1)
typedef struct _Node{
    int Max, Min;
}Node;
Node f[MAXN*4][16];  /// f[i][j], [i, i + 2^j - 1], f[i][0] = [i, i]
int n;

void build_tree() /// the f[i][0] must be init
{
    int m, i, ii;
    for (m = 1; (1<<m) <= n+1; m++) {
        for (i = 1; i+(1<<m)-1 <= n; i++) {
            f[i][m] = f[i][m-1];
            ii = i + (1<<(m-1));
            if (f[i][m].Max < f[ii][m-1].Max) {
                f[i][m].Max = f[ii][m-1].Max;
            }
            if (f[i][m].Min > f[ii][m-1].Min) {
                f[i][m].Min = f[ii][m-1].Min;
            }
        }
    }
}
Node find_max_min(int l, int r)
{
    int m, ii;
    Node nd;
    for (m = 0; ((1<<(m+1)) < (r-l+1)); m++) { /// 
    }
    nd = f[l][m];
    ii = r-(1<<m) + 1;
    if (nd.Max < f[ii][m].Max) {
        nd.Max = f[ii][m].Max;
    }
    if (nd.Min > f[ii][m].Min) {
        nd.Min = f[ii][m].Min;
    }
    return nd;
}
int main()
{
    int i, q, a, b, h, M;
    Node nd;
    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; i++) {
        scanf("%d", &h);
        f[i][0].Max = f[i][0].Min = h;
    }
    build_tree();
    for (i = 0; i < q; i++) {
        scanf("%d %d", &a, &b);
        nd = find_max_min(a, b);
        printf("%d\n", nd.Max - nd.Min);
    }
    return 0;
}

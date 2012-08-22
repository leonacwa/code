/*poj 3134 Power Calculus */
/** 计算x^n次方的最短步骤 */
#include <stdio.h>
#define MAXN 1024
#define MAXD 20
int ss[MAXD], ans[(MAXN<<1)+1], dmax;

void dfs(int d)
{
    int i;
    if (d > dmax) {
        return;
    }
    for (i = 0; i <= d; i++) {
        ss[d+1] = ss[i] + ss[d];
        if (ss[d+1] <= (MAXN << 1) && ans[ss[d+1]] >= d+1) {
            ans[ss[d+1]] = d+1;
            dfs(d+1);
        }
        ss[d+1] = ss[d] - ss[i];
        if (ss[d+1] > 0 && ans[ss[d+1]] >= d+1) {
            ans[ss[d+1]] = d+1;
            dfs(d+1);
        }
    }
}

int main()
{
    int n, i, j, t;
    ans[1] = 0;
    for (i = 2; i <= MAXN; i++) { /// 求上界
        ans[i] = 0;
        for (j = 0, t=i; t > 1; j++, t >>= 1) {
            if (t&1) {
                ans[i]++;
            }
        }
        ans[i] += j;
    }
    dmax = MAXD;
    ss[0] = 1;
    dfs(0);

    while (~scanf("%d", &n), n) {
        printf("%d\n", ans[n]);
    }
    return 0;
}

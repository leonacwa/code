/* F  Machine scheduling */
#include <stdio.h>

typedef long long llong;

#define MOD_NUM 1000000007LL

int n, r, k, m;
llong cnt, ans;

llong exp_mod(int a, int b)
{
    if (b == 0) return 1LL;
    if (b == 1) return ((llong)a) % MOD_NUM;
    llong res = exp_mod(a, b/2);
    if (b&1) res *= a;
    return res % MOD_NUM;
}

void dfs(int start, int r)
{
    if (r == 0) {
        if (start <= n) {
            cnt = (cnt+n-start+1) % MOD_NUM;
        }
        return;
    }
    int i;
    for (i = start; i + r*k <= n; i++) {
        dfs(i+k, r-1);
    }
}

int main()
{
    while (~scanf("%d %d %d %d", &n, &r, &k, &m)) {
        cnt = 0;
        //dfs(1, r-1);
        ans = cnt * exp_mod(m<r?m:r, r);
        //printf("%lld %lld\n", cnt, exp_mod(m<r?m:r, r));
        printf("%lld\n", ans);
    }
    return 0;
}

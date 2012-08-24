/* 	hdu 4016	 Magic Bitwise And Operation */
#include <stdio.h>
#include <stdlib.h>
#define INT64_MAX 0x7fffffffffffffffLL

__int64 a[41], sum[41], ans;
int n, k;

int int64_cmp(const void*a, const void *b)
{
    __int64 ret = *(__int64*)a - *(__int64*)b;
    if (ret < 0LL) return -1;
    if (ret > 0LL) return 1;
    return 0;
}

void dfs(int i, int d, __int64 num)
{
    __int64 s;
    if (ans > num) ans = num;
    if (i >= n || d >= k) return;
    s = num;
    s &= sum[i];
    if (s >= ans) return;
    //printf("%I64d\n", ans);
    dfs(i+1, d+1, a[i]&num);
    dfs(i+1, d, num);
}

int main()
{
    int tt, cs, i;
    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        scanf("%d %d", &n, &k);
        for (i = 0; i < n; i++)  scanf("%I64d", &a[i]);
        qsort(a, n, sizeof(__int64), int64_cmp);
        //for (i = 0; i < n; i++) printf("%I64d \n", a[i]); puts("");
        sum[n-1] = a[n-1];
        for (i = n-2; i >= 0; i--)  sum[i] = a[i] & sum[i+1]; /* 为了剪枝优化 */
        ans = INT64_MAX;
        dfs(0, 0, INT64_MAX);
        printf("Case #%d: %I64d\n", cs, ans);
    }
    return 0;
}

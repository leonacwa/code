/* To Miss Our Children Time */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1001

struct Block {
    long long l, w, h;
    int type;
};
Block b[MAXN];
long long dp[MAXN];

inline bool cmp_block(const Block&a, const Block&b)
{
    if (a.l != b.l) return a.l < b.l;
    if (a.w != b.w) return a.w < b.w;
    return a.type > b.type;
}

int main()
{
    int n, i, j;
    long long tmp, ans;
    while (~scanf("%d", &n) && n) {
        for (i = 0; i < n; i++) {
            scanf("%I64d %I64d %I64d %d", &b[i].l, &b[i].w, &b[i].h, &b[i].type);
            if (b[i].l < b[i].w) {tmp = b[i].l; b[i].l = b[i].w; b[i].w = tmp;}
        }
        sort(b, b+n, cmp_block);
        ans = 0LL;
        for (i = 0; i < n; i++) {
            dp[i] = b[i].h;
            for (j = 0; j < i; j++) {
                if (0 == b[i].type) {
                    if (b[i].l >= b[j].l && b[i].w >= b[j].w && dp[i]<dp[j]+b[i].h) {
                        dp[i] = dp[j]+b[i].h;
                    }
                }
                else if (1 == b[i].type) { /* 应该是我的英语不好，读不懂1的情况?? */
                    if (b[i].l >= b[j].l && b[i].w >= b[j].w && (b[i].l>b[j].l||b[i].w>b[j].w) &&
                        dp[i]<dp[j]+b[i].h)
                    {
                        dp[i] = dp[j]+b[i].h;
                    }
                }
                else if (2 == b[i].type) {
                    if (b[i].l > b[j].l && b[i].w > b[j].w && dp[i]<dp[j]+b[i].h) {
                        dp[i] = dp[j]+b[i].h;
                    }
                }
            }
            if (ans < dp[i]) ans = dp[i];
        }
        printf("%I64d\n", ans);
    }
    return 0;
}

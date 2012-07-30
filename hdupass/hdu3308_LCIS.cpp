/*
线段树
写的时候把query函数写错了，导致一直TLE，粗心害死人啊
*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
int lSum[MAXN<<2], rSum[MAXN<<2], mSum[MAXN<<2], lV[MAXN<<2], rV[MAXN<<2], cover[MAXN<<2];
int a[MAXN];

void PushUp(int rt, int L, int R)
{
    int m = R - L + 1, M = (L + R) >> 1;
    lSum[rt] = lSum[rt<<1];
    rSum[rt] = rSum[rt<<1|1];
    if (m-(m>>1) == lSum[rt] && a[M] < a[M+1]) lSum[rt] += lSum[rt<<1|1];
    if ((m>>1) == rSum[rt] && a[M] < a[M+1]) rSum[rt] += rSum[rt<<1];
    mSum[rt] = max(a[M]<a[M+1] ? rSum[rt<<1]+lSum[rt<<1|1] : 0, max(mSum[rt<<1], mSum[rt<<1|1]));
}

void build(int rt, int L, int R)
{
    if (L == R) {
        lSum[rt] = rSum[rt] = mSum[rt] = 1;
        cover[rt] = 0;
        return;
    }
    int M = (L + R) >> 1;
    build(rt<<1, L, M);
    build(rt<<1|1, M+1, R);
    PushUp(rt, L, R);
}

void update(int rt,int L, int R, int p, int v)
{
    if (p == L && R == p) {
        a[p] = v;
        return;
    }
    if (L == R) return;
    int M = (L + R) >> 1;
    if (p <= M) update(rt<<1, L, M, p, v);
    if (M < p) update(rt<<1|1, M+1, R, p, v);
    PushUp(rt, L, R);
}

int query(int rt, int L, int R, int l, int r) // 粗心害死人
{
    if (l <= L && R <= r) {
        return mSum[rt];
    }
    if (L == R) return 0;
    int M = (L + R) >> 1;
    int ret = 0;
    if (a[M] < a[M+1] && l <= M && M < r) ret = min(M - l + 1, rSum[rt<<1]) + min(r - M, lSum[rt<<1|1]);
    if (l <= M) ret = max(ret, query(rt<<1, L, M, l, r));
    if (M < r) ret = max(ret, query(rt<<1|1, M+1, R, l, r));
    return ret;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        build(1, 1, n);
        while (m--) {
            char op[32];
            int a, b;
            scanf("%s %d %d", op, &a, &b);
            if ('Q' == op[0]) {
                ++a, ++b;
                printf("%d\n", query(1, 1, n, a, b));
            } else if ('U' == op[0]) {
                ++a;
                update(1, 1, n, a, b);
            } else {
            }
        }
    }
    return 0;
}

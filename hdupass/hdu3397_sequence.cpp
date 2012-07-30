/*
线段树
对于区间异或操作的，要分情况使用，有些能延迟操作，但是有些不能延迟操作
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100000 + 10;

int cnt[MAXN<<2], lcon[MAXN<<2], rcon[MAXN<<2], mcon[MAXN<<2];
int cover[MAXN<<2], lv[MAXN<<2], rv[MAXN<<2];
int s[MAXN];

void Xor(int rt, int m)
{
    if (cover[rt] != -1) {
        cover[rt] ^= 1;
        lv[rt] = rv[rt] = cover[rt];
        cnt[rt] = lcon[rt] = rcon[rt] = mcon[rt] = cover[rt] ? m : 0;
    }
}

void PushUp(int rt, int L, int R)
{
    int m = R - L + 1, M = (L + R) >> 1;
    cnt[rt] = cnt[rt<<1] + cnt[rt<<1|1];
    lcon[rt] = lcon[rt<<1];
    rcon[rt] = rcon[rt<<1|1];
    lv[rt] = lv[rt<<1];
    rv[rt] = rv[rt<<1|1];
    if (m-(m>>1) == lcon[rt]) lcon[rt] += lcon[rt<<1|1];
    if ((m>>1) == rcon[rt]) rcon[rt] += rcon[rt<<1];
    mcon[rt] = max( (rv[rt<<1]==1&&lv[rt<<1|1]==1) ? rcon[rt<<1]+lcon[rt<<1|1] : 0,
                   max(mcon[rt<<1], mcon[rt<<1|1]) );
}

void PushDown(int rt, int L, int R)
{
    if (cover[rt] != -1) {
        cover[rt<<1] = cover[rt<<1|1] = cover[rt];
        if (cover[rt]) {
            int m = R - L + 1;
            lv[rt<<1] = rv[rt<<1] = lv[rt<<1|1] = rv[rt<<1|1] = 1;
            cnt[rt<<1] = lcon[rt<<1] = rcon[rt<<1] = mcon[rt<<1] = m - (m>>1);
            cnt[rt<<1|1] = lcon[rt<<1|1] = rcon[rt<<1|1] = mcon[rt<<1|1] = (m>>1);
        } else {
            lv[rt<<1] = rv[rt<<1] = lv[rt<<1|1] = rv[rt<<1|1] = 0;
            cnt[rt<<1] = lcon[rt<<1] = rcon[rt<<1] = mcon[rt<<1] = 0;
            cnt[rt<<1|1] = lcon[rt<<1|1] = rcon[rt<<1|1] = mcon[rt<<1|1] = 0;
        }
        cover[rt] = -1;
    }
}

void build(int rt, int L, int R)
{
    cover[rt] = -1; // 线段树初始化很重要，每个成员变量代表的含义必须明确
    if (L == R) {
        cnt[rt] = lcon[rt] = rcon[rt] = mcon[rt] = cover[rt] = s[L];
        lv[rt] = rv[rt] = s[L];
        return;
    }
    int M = (L + R) >> 1;
    build(rt<<1, L, M);
    build(rt<<1|1, M+1, R);
    PushUp(rt, L, R);
}

void update(int rt, int L, int R, int l, int r, int c)
{
    if (l <= L && R <= r) {
        if (0 == c) {
            cover[rt] = lv[rt] = rv[rt] = cnt[rt] = lcon[rt] = rcon[rt] = mcon[rt] = 0;
        } else if (1 == c) {
            cover[rt] = 1;
            lv[rt] = rv[rt] = 1;
            cnt[rt] = lcon[rt] = rcon[rt] = mcon[rt] = R - L + 1;
        } else if (2 == c) {
            if (cover[rt] != -1) Xor(rt, R-L+1);
            else {
                PushDown(rt, L, R);
                int M = (L + R) >> 1;
                update(rt<<1, L, M, l, r, c);
                update(rt<<1|1, M+1, R, l, r, c);
                PushUp(rt, L, R);
            }
        }
        return;
    }
    if (L == R) return;
    PushDown(rt, L, R);
    int M = (L + R) >> 1;
    if (l <= M) update(rt<<1, L, M, l, r, c);
    if (M < r) update(rt<<1|1, M+1, R, l, r, c);
    PushUp(rt, L, R);
}

int query3(int rt, int L, int R, int l, int r)
{
    if (l <= L && R <= r) {
        return cnt[rt];
    }
    if (L == R) return 0;
    int ret = 0, M = (L + R) >> 1;
    PushDown(rt, L, R);
    if (l <= M) ret += query3(rt<<1, L, M, l, r);
    if (M < r) ret += query3(rt<<1|1, M+1, R, l, r);
    return ret;
}

int query4(int rt, int L, int R, int l, int r)
{
    if (l <= L && R <= r) {
        return mcon[rt];
    }
    if (L == R) return 0;
    int ret = 0, M = (L + R) >> 1;
    PushDown(rt, L, R);
    if (l <= M) ret = max(ret, query4(rt<<1, L, M, l, r));
    if (M < r) ret = max(ret, query4(rt<<1|1, M+1, R, l, r));
    if (l <= M && M < r && rv[rt<<1] == 1 && lv[rt<<1|1] == 1) {
        ret = max(ret, min(M - l + 1, rcon[rt<<1]) + min(r - M, lcon[rt<<1|1]));
    }
    return ret;
}

int main()
{
    int nTest;
    scanf("%d", &nTest);
    while (nTest--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) scanf("%d", &s[i]);
        build(1, 1, n);
        while (m--) {
            int c, a, b;
            scanf("%d%d%d", &c, &a, &b);
            ++a, ++b;
            if (0 == c) {
                update(1, 1, n, a, b, c);
            } else if (1 == c) {
                update(1, 1, n, a, b, c);
            } else if (2 == c) {
                update(1, 1, n, a, b, c);
            } else if (3 == c) {
                printf("%d\n", query3(1, 1, n, a, b));
            } else if (4 == c) {
                printf("%d\n", query4(1, 1, n, a, b));
            } else {
            }
        }
    }
    return 0;
}

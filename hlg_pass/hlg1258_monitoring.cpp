#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int64;

const int MAXN = 100000 * 2 + 100;
struct Seg {
    int l, r, y, v;
    Seg(int tl=0, int tr=0, int ty=0, int tv=0) : l(tl), r(tr), y(ty), v(tv) {}
    bool operator < (const Seg &B) const {
        if (y != B.y) return y < B.y;
        return v < B.v;
    }
} ss[MAXN];

int len1[MAXN<<2], len2[MAXN<<2], len3[MAXN<<2];
int cnt[MAXN<<2];
int xa[MAXN];

#define CLR(A) memset(A, 0, sizeof(A))
void init()
{
    CLR(len1);
    CLR(len2);
    CLR(len3);
    CLR(cnt);
}

void PushUp(int rt, int L, int R)
{
    int LS = rt<<1, RS = rt<<1|1;

    if (cnt[rt] > 0) {
        len1[rt] = xa[R] - xa[L-1];
    } else if (L == R) {
        len1[rt] = 0;
    } else {
        len1[rt] = len1[LS] + len1[RS];
    }

    if (cnt[rt] > 1) {
        len2[rt] = xa[R] - xa[L-1];
    } else if (L == R) {
        len2[rt] = 0;
    } else if (cnt[rt] > 0) {
        len2[rt] = len1[LS] + len1[RS];
    } else {
        len2[rt] = len2[LS] + len2[RS];
    }

    if (cnt[rt] > 2) {
        len3[rt] = xa[R] - xa[L-1];
    } else if (L == R) {
        len3[rt] = 0;
    } else if (cnt[rt] > 1) {
        len3[rt] = len1[LS] + len1[RS];
    } else if (cnt[rt] > 0) {
        len3[rt] = len2[LS] + len2[RS];
    } else {
        len3[rt] = len3[LS] + len3[RS];
    }
}

void update(int rt, int L, int R, int l, int r, int c)
{
    if (l <= L && R <= r) {
        cnt[rt] += c;
        PushUp(rt, L, R);
        return;
    }
    int M = (L + R) >> 1;
    if (l <= M) update(rt<<1, L, M, l, r, c);
    if (M < r) update(rt<<1|1, M+1, R, l, r, c);
    PushUp(rt, L, R);
}

int bin(int n, int x)
{
    int l = 0, r = n-1, m;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (xa[m] == x) return m;
        if (xa[m] < x)  l = m + 1;
        else r = m - 1;
    }
    return -1;
}

int main()
{
    init();
    int n;
    while (EOF != scanf("%d", &n)) {
        int m = 0, xc = 0;
        for (int i = 0; i < n; ++i) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            ss[m++] = Seg(a, c, b, 1);
            ss[m++] = Seg(a, c, d, -1);
            xa[xc++] = a;
            xa[xc++] = c;
        }
        sort(xa, xa + xc);
        int t = 1;
        for (int i = 1; i < xc; ++i) {
            if (xa[i-1] != xa[i]) xa[t++] = xa[i];
        }
        xc = t;
        sort(ss, ss+m);
        ss[m].y = ss[m-1].y;
        int64 ans = 0;
        for (int i = 0; i < m; ++i) {
            if (ss[i].l < ss[i].r) update(1, 1, xc-1, bin(xc, ss[i].l)+1, bin(xc, ss[i].r), ss[i].v);
            ans += (int64)(ss[i+1].y - ss[i].y) * (len2[1] - len3[1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

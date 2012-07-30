#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 2*10000 + 100;
struct Seg {
    int l, r, y, v;
    Seg(int tl = 0, int tr = 0, int ty = 0, int tv = 0) : l(tl), r(tr), y(ty), v(tv) {}
    bool operator < (const Seg &B) const {
        return y < B.y;
    }
} ss[MAXN];

int cnt[MAXN<<2], len[MAXN<<2], yseg[MAXN<<2], ly[MAXN<<2], ry[MAXN<<2];

#define CLR(A) memset(A, 0, sizeof(A))
void build(int rt, int L, int R)
{
    CLR(cnt);
    CLR(len);
    CLR(yseg);
    CLR(ly);
    CLR(ry);
}

void PushUp(int rt, int L, int R)
{
    if (cnt[rt]) {
        yseg[rt] = 2;
        ly[rt] = ry[rt] = 1;
        len[rt] = R - L + 1;
    } else if (L == R) {
        yseg[rt] = ly[rt] = ry[rt] = len[rt] = 0;
    } else {
        int LS = rt<<1, RS = rt<<1|1;
        ly[rt] = ly[LS], ry[rt] = ry[RS];
        len[rt] = len[LS] + len[RS];
        yseg[rt] = yseg[LS] + yseg[RS];
        if (ry[LS] && ly[RS]) yseg[rt] -= 2;
    }
}

void update(int rt, int L, int R, int l, int r, int c)
{
    if (l <= L && R <= r) {
        cnt[rt] += c;
        PushUp(rt, L, R);
        return;
    }
    int M = L + (R - L) / 2;
    if (l <= M) update(rt<<1, L, M, l, r, c);
    if (M < r) update(rt<<1|1, M+1, R, l, r, c);
    PushUp(rt, L, R);
}

int main()
{
    int n, m;
    while (EOF != scanf("%d", &n)) {
        m = 0;
        int left = MAXN, right = -MAXN;
        for (int i = 0; i < n; ++i) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            left = min(left, a);
            right = max(right, c);
            ss[m++] = Seg(a, c, b, 1);
            ss[m++] = Seg(a, c, d, -1);
        }
        sort(ss, ss+m);
        build(1, left, right-1);
        int ans = 0, last = 0;
        for (int i = 0; i < m;  ++i) {
            if (ss[i].l < ss[i].r) update(1, left, right-1, ss[i].l, ss[i].r-1, ss[i].v);
            ans += yseg[1] * (ss[i+1].y - ss[i].y);
            ans += abs(len[1] - last);
            last = len[1];
        }
        printf("%d\n", ans);
    }
    return 0;
}

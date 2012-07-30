#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2*1000 + 100;

struct Seg {
    double l, r, y;
    int v;
    Seg(double tl = 0, double tr = 0, double ty = 0, int tv = 0) : l(tl), r(tr), y(ty), v(tv) {}
    bool operator < (const Seg &B) const {
        return y < B.y;
    }
} ss[MAXN];

double len[MAXN<<2];
double clen[MAXN<<2];
int cnt[MAXN<<2];
double xa[MAXN];

int bin(int n, double x)
{
    int l = 0, r = n-1, m;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (xa[m] == x) return m;
        if (xa[m] < x) l = m + 1;
        else r = m - 1;
    }
    while(1);
    return -1;
}

#define CLR(A) memset(A, 0, sizeof(A))
void init()
{
    CLR(len);
    CLR(clen);
    CLR(cnt);
}

void PushUp(int rt, int L, int R)
{
    if (cnt[rt] > 0) {
        len[rt] = xa[R] - xa[L-1];
    } else if (L == R) {
        len[rt] = 0;
    } else {
        len[rt] = len[rt<<1] + len[rt<<1|1];
    }
    if (cnt[rt] > 1) {
        clen[rt] = xa[R] - xa[L-1];
    } else if (L == R) {
        clen[rt] = 0;
    } else if (cnt[rt] > 0) {
        clen[rt] = len[rt<<1] + len[rt<<1|1];
    } else {
        clen[rt] = clen[rt<<1] + clen[rt<<1|1];
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
    //int M = L + (R - L) / 2;
    if (l <= M) update(rt<<1, L, M, l, r, c);
    if (M < r) update(rt<<1|1, M+1, R, l, r, c);
    PushUp(rt, L, R);
}

int main()
{
    //freopen("p.in", "r", stdin);
    int nTest;
    scanf("%d", &nTest);
    while  (nTest--) {
        int n, m = 0, xc = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            ss[m++] = Seg(x1, x2, y1, 1);
            ss[m++] = Seg(x1, x2, y2, -1);
            xa[xc++] = x1;
            xa[xc++] = x2;
        }
        sort(ss, ss + m);
        ss[m].y = ss[m-1].y;
        sort(xa, xa+xc);
        int t = 1;
        for (int i = 1; i < xc; ++i) {
            if (xa[i-1] != xa[i]) xa[t++] = xa[i];
        }
        xc = t;
        double ans = 0;
        init();
        for (int i = 0; i < m; ++i) {
            if (ss[i].l < ss[i].r) update(1, 1, xc-1, bin(xc, ss[i].l)+1, bin(xc, ss[i].r), ss[i].v);
            ans += (ss[i+1].y - ss[i].y) * clen[1];
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}

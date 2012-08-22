#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2222;
struct Seg {
    int v;
    double l, r, y;
    Seg(double tl = 0, double tr = 0, double ty = 0, int tv = 0) : l(tl), r(tr), y(ty), v(tv) {}
    bool operator < (const Seg &B) const {
        return y < B.y;
    }
} ss[MAXN];

double len[MAXN<<2];
int cnt[MAXN<<2];
double xa[MAXN];

#define CLR(A) memset(A, 0, sizeof(A))
void init()
{
    CLR(len);
    CLR(cnt);
}

void PushUp(int rt, int L, int R)
{
    if (cnt[rt]) {
        len[rt] = xa[R] - xa[L-1];
    } else if (L == R) {
        len[rt] = 0;
    } else {
        len[rt] = len[rt<<1] + len[rt<<1|1];
    }
}

void update(int rt, int L, int R, int l, int r, int c)
{
    if (l <= L && R <= r) {
        cnt[rt] += c;
        PushUp(rt, L, R);
        return;
    }
    //if (L == R) return;
    int M = (R - L) / 2 + L;
    if (l <= M) update(rt<<1, L, M, l, r, c);
    if (M < r)  update(rt<<1|1, M+1, R, l, r, c);
    PushUp(rt, L, R);
}

int bin(int n, double x)
{
    int l = 0, r = n-1, m;
    while (l <= r) {
        m = (r - l) / 2 + l;
        if (xa[m] == x) return m;
        if (xa[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

int main()
{
    int n, nCase = 0;
    while (EOF != scanf("%d", &n) && n > 0) {
        int m = 0, xa_cnt = 0;
        for (int i = 0; i < n; ++i) {
            double x1, x2, y1, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            ss[m++] = Seg(x1, x2, y1, 1);
            ss[m++] = Seg(x1, x2, y2, -1);
            xa[xa_cnt++] = x1;
            xa[xa_cnt++] = x2;
        }
        sort(ss, ss+m);
        ss[m].y = ss[m-1].y;
        sort(xa, xa + xa_cnt);
        int t = 1;
        for (int i = 1; i < xa_cnt; ++i) {
            if (xa[i-1] != xa[i]) xa[t++] = xa[i];
        }
        xa_cnt = t;
        init();
        double ans = 0;
        for (int i = 0; i < m; ++i) {
            if (ss[i].l < ss[i].r) {
                update(1, 1, xa_cnt-1, bin(xa_cnt, ss[i].l)+1, bin(xa_cnt, ss[i].r), ss[i].v);
            }
            //printf("%d: len %lf, h %lf\n", i, len[1], ss[i+1].y - ss[i].y);
            ans += (ss[i+1].y - ss[i].y) * len[1];
        }
        printf("Test case #%d\n"
               "Total explored area: %.2lf\n\n", ++nCase, ans);
    }
    return 0;
}

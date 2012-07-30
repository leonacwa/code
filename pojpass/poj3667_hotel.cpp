#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int SumN = 50000 + 10;
struct Node {
    int mSum, // 区间中的最大值
        lSum, // 左起的最大连续值
        rSum; // 右起的最大连续值
    int clr;
} T[SumN<<2];

void PushDown(int rt, int m)
{
    if (T[rt].clr != -1) {
        T[rt<<1].clr = T[rt<<1|1].clr = T[rt].clr;
        int s = rt<<1;
        T[s].mSum = T[s].lSum = T[s].rSum = T[rt].clr ? 0 : m - (m>>1);
        s |= 1;
        T[s].mSum = T[s].lSum = T[s].rSum = T[rt].clr ? 0 : (m>>1);
        T[rt].clr = -1;
    }
}

void PushUp(int rt, int m)
{
    T[rt].lSum = T[rt<<1].lSum;
    T[rt].rSum = T[rt<<1|1].rSum;
    if (T[rt].lSum == m - (m>>1)) T[rt].lSum += T[rt<<1|1].lSum;
    if (T[rt].rSum == (m>>1)) T[rt].rSum += T[rt<<1].rSum;
    T[rt].mSum = max(T[rt<<1].rSum + T[rt<<1|1].lSum, max(T[rt<<1].mSum, T[rt<<1|1].mSum));
}

void build(int rt, int L, int R)
{
    T[rt].clr = 0;
    T[rt].mSum = T[rt].lSum = T[rt].rSum = R - L + 1;
	return;
    if (L == R) return;
    int m = (L + R) >> 1;
    build(rt<<1, L, m);
    build(rt<<1|1, m+1, R);
}

void update(int rt, int L, int R, int l, int r, bool clr)
{
    if (l <= L && R <= r) {
        T[rt].clr = clr;
        T[rt].mSum = T[rt].lSum = T[rt].rSum = clr ? 0 : R - L + 1;
        return;
    }
    if (L == R) return;
    PushDown(rt, R-L+1);
    int m = (L + R) >> 1;
    if (l <= m) update(rt<<1, L, m, l, r, clr);
    if (m < r) update(rt<<1|1, m+1, R, l, r, clr);
    PushUp(rt, R-L+1);
}

int query(int rt, int L, int R, int d)
{
    if (L == R) return L;
    PushDown(rt, R-L+1);
    int m = (L + R) >> 1;
    if (T[rt<<1].mSum >= d) return query(rt<<1, L, m, d);
    else if (T[rt<<1].rSum + T[rt<<1|1].lSum >= d) return m - T[rt<<1].rSum + 1;
    else  query(rt<<1|1, m+1, R, d);
}

int main()
{
    int n, m;
    while (EOF != scanf("%d%d", &n, &m)) {
        build(1, 1, n);
        while(m--) {
            int a, x, d;
            scanf("%d", &a);
            if (1 == a) {
                scanf("%d", &d);
                if (T[1].mSum < d) {
                    puts("0");
                } else {
                    int r = query(1, 1, n, d);
                    printf("%d\n", r);
                    update(1, 1, n, r, r+d-1, 1);
                }
            } else if (2 == a) {
                scanf("%d%d", &x, &d);
                update(1, 1, n, x, x+d-1, 0);
            } else ;
        }
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10000 + 100;

int col[MAXN<<4];
bool paint[MAXN];
int li[MAXN], ri[MAXN];
int X[MAXN << 2]; // 这个数组要开大，不然会不够存而外加的坐标

void PushDown(int rt)
{
    if (col[rt] != -1) {
        col[rt<<1] = col[rt<<1|1] = col[rt];
        col[rt] = -1;
    }
}

void update(int rt, int L, int R, int l, int r, int c)
{
    if (l <= L && R <= r) {
        col[rt] = c;
        return;
    }
    PushDown(rt);
    int m = (L + R) >> 1;
    if (l <= m) update(rt<<1, L, m, l, r, c);
    if (m < r) update(rt<<1|1, m+1, R, l, r, c);
}

int query(int rt, int L, int R)
{
    if (col[rt] != -1) {
        if (!paint[col[rt]]) {
            paint[col[rt]] = true;
            return 1;
        }
        return 0;
    }
    if (L == R) return 0;
    int m = (L + R) >> 1;
    return query(rt<<1, L, m) + query(rt<<1|1, m+1, R);
}
/*  // 这个二分也是AC的
int bin(int X[], int n, int v)
{
    int l = 0, r = n- 1, m;
    while (l <= r) {
        m = (r - l) / 2 + l;
        if (X[m] == v) return m;
        if (X[m] < v) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
*/
int bin(int X[], int n, int v)
{
    int l = 0, r = n- 1, m;
    while (l < r) {
        m = (r - l) / 2 + l;
        if (X[m] < v) l = m + 1;
        else r = m;
    }
    return l;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int m = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &li[i], &ri[i]);
            X[m++] = li[i];
            X[m++] = ri[i];
        }
        sort(X, X + m);
        int t = m;
        m = 1;
        for (int i = 1; i < t; ++i) {
            if (X[i] != X[i-1]) X[m++] = X[i];
        }
        for (int i = m - 1; i > 0; --i) {
            if (X[i] != X[i-1]+1) X[m++] = X[i-1] + 1;
        }
        sort(X, X + m);
        memset(col, -1, sizeof(col));
        for (int i = 0; i < n; ++i) {
            int l = bin(X, m, li[i]);
            int r = bin(X, m, ri[i]);
            update(1, 0, m, l, r, i);
        }
        memset(paint, 0, sizeof(paint));
        printf("%d\n", query(1, 0, m));
    }
	return 0;
}

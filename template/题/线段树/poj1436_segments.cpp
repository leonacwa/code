#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 8005;
const int MAXN2 = 8005<<1;

struct Seg {
    int y1, y2, x;
    bool operator < (const Seg &B) const {
        return x < B.x;
    }
} seg[MAXN];

int sid[MAXN2<<2];
bool g[MAXN][MAXN];

void PushDown(int rt)
{
    if (sid[rt] != -1) {
        sid[rt<<1] = sid[rt<<1|1] = sid[rt];
        sid[rt] = -1;
    }
}

void update(int rt, int L, int R, int l, int r, int id)
{
    if (l <= L && R <= r) {
        sid[rt] = id;
        return;
    }
    if (L == R) return;
    PushDown(rt);
    int m = (L + R) >> 1;
    if (l <= m) update(rt<<1, L, m, l, r, id);
    if (m < r) update(rt<<1|1, m+1, R, l, r, id);
}

void query(int rt, int L, int R, int l, int r, int id)
{
    if (sid[rt] != -1 && l <= L && R <= r) {
        g[sid[rt]][id] = true; //g[id][sid[rt]] = true;
        return;
    }
    if (L == R) return;
    PushDown(rt);
    int m = (L + R) >> 1;
    if (l <= m) query(rt<<1, L, m, l, r, id);
    if (m < r) query(rt<<1|1, m+1, R, l, r, id);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d", &seg[i].y1, &seg[i].y2, &seg[i].x);
            seg[i].y1 <<= 1;
            seg[i].y2 <<= 1;
        }
        sort(seg+1, seg+1+n);
        memset(sid, 0, sizeof(sid));
        memset(g, 0, sizeof(g));
        for (int i = 1; i <= n; ++i) {
            query(1, 0, MAXN2, seg[i].y1, seg[i].y2, i);
            update(1, 0, MAXN2, seg[i].y1, seg[i].y2, i);
        }
        int ans = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (g[i][j]) {
                    for (int k = j+1; k <= n; ++k) {
                        if (g[j][k] && g[i][k]) {
                            ++ans;
                        }
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

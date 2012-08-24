#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 50000 + 10;

struct Node {
    int id, lsum, rsum, msum, blks, lv, rv;
} T[MAXN<<2];
int ID;
int start[MAXN], end[MAXN];

void Reset(int rt, int L, int R)
{
    ID = 0;
    T[rt].id = 0;
    T[rt].blks = 0;
    T[rt].lsum = T[rt].rsum = T[rt].msum = R - L + 1;
    T[rt].lv = T[rt].rv = 0;
}

void PushDown(int rt, int L, int R)
{
    if (T[rt].id != -1) {
        int LS = rt<<1, RS = rt<<1|1, m = R - L + 1;
        T[LS].id = T[RS].id = T[rt].id;
        T[LS].lv = T[LS].rv = T[RS].lv = T[RS].rv = T[rt].id;
        T[LS].lsum = T[LS].rsum = T[LS].msum = T[rt].id ? 0 : m - (m>>1);
        T[RS].lsum = T[RS].rsum = T[RS].msum = T[rt].id ? 0 : (m>>1);
        T[LS].blks = T[RS].blks = T[rt].id ? 1 : 0;
        T[rt].id = -1;
    }
}

void PushUp(int rt, int L, int R)
{
    int LS = rt<<1, RS = rt<<1|1, m = (R - L + 1);
    T[rt].lsum = T[LS].lsum;
    T[rt].rsum = T[RS].rsum;
    T[rt].lv = T[LS].lv;
    T[rt].rv = T[RS].rv;
    if (T[rt].lsum == m-(m>>1)) T[rt].lsum += T[RS].lsum;
    if (T[rt].rsum == (m>>1)) T[rt].rsum += T[LS].rsum;
    T[rt].msum = max(T[LS].rsum+T[RS].lsum, max(T[LS].msum, T[RS].msum));
    T[rt].blks = T[LS].blks + T[RS].blks;
    if (T[LS].rv > 0 && T[LS].rv == T[RS].lv) T[rt].blks--;
}

void update(int rt, int L, int R, int l, int r, int c)
{
    if (l <= L && R <= r) {
        T[rt].id = c;
        T[rt].lv = T[rt].rv = c;
        if (c == 0) {
            T[rt].lsum = T[rt].rsum = T[rt].msum = R - L + 1;
            T[rt].blks = 0;
        } else {
            T[rt].lsum = T[rt].rsum = T[rt].msum = 0;
            T[rt].blks = 1;
        }
        return;
    }
    if (L == R) return;
    int M = (L + R) >> 1;
    PushDown(rt, L, R);
    if (l <= M) update(rt<<1, L, M, l, r, c);
    if (M < r) update(rt<<1|1, M+1, R, l, r, c);
    PushUp(rt, L, R);
}

int New(int rt, int L, int R, int x)
{
    if (T[rt].msum < x || x <= 0) return 0;
    if (T[rt].lsum >= x) {
        update(rt, L, R, L, L+x-1, ++ID);
        start[ID] = L;
        end[ID] = L+x-1;
        return L;
    }
    PushDown(rt, L, R);
    int M = (L + R) >> 1, LS = rt<<1, RS = rt<<1|1, ret = 0;
    if (T[LS].msum >= x) ret = New(LS, L, M, x);
    else if (T[LS].rsum > 0 && T[RS].lsum > 0 && T[LS].rsum+T[RS].lsum >= x) {
        /* // 下面是一直让我WA的代码
        int t = x - T[LS].rsum;
        ret = New(LS, L, M, T[LS].rsum); //没仔细想，其实很有可能在左起连续区间申请，而导致错误
        --ID;
        New(RS, M+1, R, t);
        start[ID] = ret;
        */
        ret = M - T[LS].rsum + 1;
        update(rt, L, R, ret, ret+x-1, ++ID);
        start[ID] = ret;
        end[ID] = ret+x-1;
    } else {
        ret = New(RS, M+1, R, x);
    }
    PushUp(rt, L, R);
    return ret;
}

int queryid(int rt, int L, int R, int x)
{
    if (T[rt].id == 0) return 0;
    if (L <= x && x <= R && T[rt].id != -1) {
        return T[rt].id;
    }
    int M = (L + R) >> 1;
    if (x <= M) return queryid(rt<<1, L, M, x);
    if (M < x) return queryid(rt<<1|1, M+1, R, x);
    return -1;
}

bool Free(int n, int x, int &A, int &B) // xth address
{
    A = B = 0;
    int id = queryid(1, 1, n, x);
    if (id <= 0) return false;

    A = start[id];
    B = end[id];
    if (A == 0 || B == 0) return false;
    update(1, 1, n, A, B, 0);
    start[id] = end[id] = 0;
    return true;
}

int Get(int rt, int L, int R, int x) // xth block
{
    if (T[rt].blks < x || x == 0) return 0;
    if (T[rt].blks == 1 && T[rt].id != -1) {
        return start[T[rt].id];
    }
    if (L == R) return 0;
    int M = (L + R) >> 1, LS = rt<<1, RS = rt<<1|1;
    if (T[LS].blks >= x) return Get(LS, L, M, x);
    return Get(RS, M+1, R, x + T[RS].blks - T[rt].blks);
}

int main()
{
    #ifdef ONLINE_JUDGE
    #else
    freopen("p.in", "r", stdin);
    //freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    while (2 == scanf("%d%d", &n, &m)) {
        Reset(1, 1, n);
        char cmd[32];
        int x;
        while(m--) {
            scanf("%s", cmd);
            if (cmd[0] == 'R') {
                Reset(1, 1, n);
                puts("Reset Now");
            } else if (cmd[0] == 'N') {
                scanf("%d", &x);
                int a = New(1, 1, n, x);
                if (a == 0) puts("Reject New");
                else printf("New at %d\n", a);
            } else if (cmd[0] == 'F') {
                scanf("%d", &x);
                int A, B;
                if (Free(n, x, A, B)) printf("Free from %d to %d\n", A, B);
                else puts("Reject Free");
            } else if (cmd[0] == 'G') {
                scanf("%d", &x);
                int a = Get(1, 1, n, x);
                if (a <= 0) puts("Reject Get");
                else printf("Get at %d\n", a);
            } else {
                while(1) ;
            }
        }
        puts("");
    }
    return 0;
}

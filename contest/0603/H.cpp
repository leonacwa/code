#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;
const int MAXN = 100000 + 10;

struct Edge {
    int to, len;
    Edge * next;
} E[MAXN * 2];
int nE;
Edge *head[MAXN];

int P[MAXN], L[MAXN];

void addEdge(int u, int v, int len) {
    Edge * e = E + nE++;
    e->to = v;
    e->len = len;
    e->next = head[u];
    head[u] = e;
}

int MaxLen, Left, Right;
void dfs(int u, int pr, int dep, int &l, int &lmax)
{
    L[u] = dep;
    P[u] = pr;
    l = u, lmax = 0;
    int r = u, rmax = 0, t, tmax, len;
    for (Edge * e = head[u]; e; e = e->next) {
        if (e->to == pr) continue;
        dfs(e->to, u, dep + 1, t, tmax);
        len = tmax + e->len;
        if (lmax < len) {
            rmax = lmax;
            r = l;
            lmax = len;
            l = t;
        } else if (rmax < len) {
            rmax = len;
            r = t;
        }
    }
    //while (MaxLen > 0 && MaxLen == lmax + rmax) ;
    if (MaxLen < lmax + rmax) {
        Left = l, Right = r;
        MaxLen = lmax + rmax;
    }
}

bool sign[MAXN];
int vex[MAXN], cnt;
int MinLen;

void dfs_len(int u, int pr, int &l, int &lmax)
{
    int t, tmax, len;
    l = u, lmax = 0;
    for (Edge *e = head[u]; e; e = e->next) {
        if (sign[e->to] || e->to == pr) continue;
        dfs_len(e->to, u, t, tmax);
        len = tmax + e->len;
        if (lmax < len) {
            lmax = len;
            l = t;
        }
    }
}

int main()
{
    int n;
    while (EOF != scanf("%d", &n) && n > 0) {
        nE = 0;
        memset(head, 0, sizeof(head));
        for (int u, v, l, i = 1; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &l);
            addEdge(u, v, l);
            addEdge(v, u, l);
        }

        MaxLen = 0, Left = 1, Right = 1;
        int l, lmax, r;
        dfs(1, -1, 1, l, lmax);
        //printf("Left %d, Right %d\n", Left, Right);
        memset(sign, 0, sizeof(sign));
        cnt = 0;
        l = Left, r = Right;
        while (l != r) {
            if (L[l] > L[r]) {
                sign[l] = true;
                vex[cnt++] = l;
                l = P[l];
            } else {
                sign[r] = true;
                vex[cnt++] = r;
                r = P[r];
            }
        }
        vex[cnt++] = l;
        sign[l] = true;
        MinLen = 0;
        for (int i = 0; i < cnt; ++i) {
            int l, lmax;
            //printf("%d.  ", vex[i]);
            dfs_len(vex[i], -1, l, lmax);
            if (lmax > MinLen) MinLen = lmax;
        }
        printf("%d\n", MinLen);
    }
    return 0;
}

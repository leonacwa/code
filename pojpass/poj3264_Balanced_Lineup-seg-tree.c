/* poj 3264 Balanced Lineup */
/// seg tree, RMQ
#include <stdio.h>
#define MAXN (50000 + 1)
#define INF (1000000 + 9999)
typedef struct _Node{
    int Max, Min;
    int l, r;
}Node;
Node tr[MAXN*8]; /// 范围加大x8就过了

int h[MAXN];
int n;
void make_tree(int x, int l, int r)
{
    tr[x].Max = -INF;
    tr[x].Min = INF;
    tr[x].l = l;
    tr[x].r = r;
    if (l == r){
        return;
    }
    //printf("l:%d r:%d\n", l, r);
    make_tree(x+x, l, l + (r-l)/2);
    make_tree(x+x+1, l + (r-l)/2 + 1, r);
}
void ins(int x, int lr, int v) /// 插入的是一个点，l==r
{
    if (tr[x]. l <= lr && lr <= tr[x].r) {
        if (tr[x].Max < v) {
            tr[x].Max = v;
        }
        if (tr[x].Min > v) {
             tr[x].Min = v;
        }
        if (lr <= tr[x].l + (tr[x].r - tr[x].l) / 2) {
            ins(x+x, lr, v);
        }
        else {
            ins(x+x+1, lr, v);
        }
    }
    else if (tr[x].l == lr && tr[x].r == lr) {
        tr[x].Max = v;
        tr[x].Min = v;
    }
}
Node find_max_min(int x, int l, int r)
{
    int mid;
    Node nd, nd2;
    if (l <= tr[x].l && tr[x].r <= r) {
        return tr[x];
    }
    nd.Min = INF;
    nd.Max = -INF;
    mid = tr[x].l+(tr[x].r-tr[x].l)/2;
    if (l <= mid) {
        nd = find_max_min(x+x, l, r);
    }
    if (mid < r) {
        nd2 = find_max_min(x+x+1, l, r);
        if (nd.Max < nd2.Max) {
            nd.Max = nd2.Max;
        }
        if (nd.Min > nd2.Min) {
            nd.Min = nd2.Min;
        }
    }
    return nd;
}
int main()
{
    int i, q, a, b;
    Node nd;
    scanf("%d %d", &n, &q);
    make_tree(1, 1, n);
    for (i = 1; i <= n; i++) {
        scanf("%d", h+i);
        ins(1, i, h[i]);
    }
    for (i = 0; i < q; i++) {
        scanf("%d %d", &a, &b);
        nd = find_max_min(1, a, b);
        printf("%d\n", nd.Max - nd.Min);
    }
    return 0;
}

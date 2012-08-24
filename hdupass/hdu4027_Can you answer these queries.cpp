/* Can you answer these queries? */
#include <stdio.h>
#include <math.h>

#define MAXN (100000+ 1)
typedef long long llong;
llong sum[MAXN*4];
llong data[MAXN];
bool one[MAXN*4];

void build_tree(int x, int left, int right)
{
    int mid;
    if (left == right) {
        sum[x] = data[left];
        one[x] = (sum[x] <= 1LL);
    } else {
        mid = (left+right)>>1;
        build_tree(x+x, left, mid);
        build_tree(x+x+1, mid+1, right);
        sum[x] = sum[x+x] + sum[x+x+1];
        one[x] = one[x+x] && one[x+x+1];
    }
}

void attack(int x, int left, int right, int l, int r)
{
    if (r < left || right < l) return;
    if (one[x]) return;
    if (left == right) {
        sum[x] = (llong)(sqrt((double)sum[x])+1e-8);
        one[x] = (sum[x] <= 1LL);
    } else {
        int mid = (left + right) >> 1;
        attack(x+x, left, mid, l, r);
        attack(x+x+1, mid+1, right, l, r);
        sum[x] = sum[x+x] + sum[x+x+1];
        one[x] = one[x+x] && one[x+x+1];
    }
}

llong query(int x, int left, int right, int l, int r)
{
    if (r < left || right < l) return 0;
    if (l <= left && right <= r) return sum[x];
    int mid = (left+right)>>1;
    return query(x+x, left, mid, l, r) + query(x+x+1, mid+1, right, l, r);
}

int main()
{
    int cs = 0;
    int type, l, r, t;
    int i, n, m;

    while (1==scanf("%d", &n)) {
        printf("Case #%d:\n", ++cs);
        for (i = 1; i <= n; i++) scanf("%I64d", &data[i]);
        build_tree(1, 1, n);
        scanf("%d", &m);
        while (m--) {
            scanf("%d %d %d", &type, &l, &r);
            if (l > r) {t = l; l = r; r = t;}
            if (type == 0)
                attack(1, 1, n, l, r);
            else if (type == 1)
                printf("%I64d\n", query(1, 1, n, l, r));
            else
                for (;;) puts("fuck you");
        }
        printf("\n");
    }
    return 0;
}

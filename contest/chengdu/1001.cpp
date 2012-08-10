/* Attack */
#include <stdio.h>
#include <string.h>

#define MAXN (20000+100)
int cool[1+MAXN*6], cnt[1+MAXN*6];
int t, n, q;

void build_tree(int n)
{
    int m = 6*n+1;
    //memset(cool, 0, sizeof(cool[0])*m);
    cool[1] = 0;
    memset(cnt, 0, sizeof(cnt[0])*m);
}

void cool_down(int x, int left, int right)
{
    if (cool[x] == 0) return;
    if (cool[x] > 0) {
        cool[x]--;
        return;
    }
    int mid = (left+right) >> 1;
    cool_down(x+x, left, mid);
    cool_down(x+x+1, mid+1, right);
    if (cool[x+x] == cool[x+x+1]) cool[x] = cool[x+x];
}

/*
int is_cool(int x, int left, int right, int lr)
{
    if (left <= lr && lr <= right && cool[x] >= 0) return cool[x];
    int mid = (left+right) >> 1;
    if (left <= lr && lr <= mid ) return is_cool(x+x, left, mid, lr);
    if (mid+1 <= lr && lr <= right ) return is_cool(x+x+1, mid+1, right, lr);
} */

void attack(int x, int left, int right, int l, int r)
{
    if (r < left || right < l) {
        cool_down(x, left, right);
        return;
    }
    int mid = (left+right)>>1;
    if (l <= left && right <= r) {
        if (cool[x] > 0) cool[x]--;
        if (cool[x] == 0) {
            cool[x] = t;
        } else if (cool[x] < 0) {
            attack(x+x, left, mid, l, r);
            attack(x+x+1, mid+1, right, l, r);
            if (cool[x+x] == cool[x+x+1]) cool[x] = cool[x+x];
        } else {
            cnt[x]++;
        }
        return;
    }
    if (cool[x] >= 0) {
        cool[x+x] = cool[x+x+1] = cool[x];
        cool[x] = -1;
    }
    attack(x+x, left, mid, l, r);
    attack(x+x+1, mid+1, right, l, r);
    if (cool[x+x] == cool[x+x+1]) cool[x] = cool[x+x];
}

int query(int x, int left, int right, int lr)
{
    if (lr < left || right < lr) return 0;
    if (left == right)  return cnt[x];
    int mid = (left+right)>>1;
    return cnt[x] + query(x+x, left, mid, lr) + query(x+x+1, mid+1, right, lr);
}

int main()
{
    int cs, tt;
    int i, l, r, tmp;
    char cmd[256];

    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        printf("Case %d:\n", cs);
        scanf("%d %d %d", &n, &q, &t);
        build_tree(n);
        while (q--) {
            scanf("%s", cmd);
            if (cmd[0] == 'Q') { // Query
                scanf("%d", &l);
                printf("%d\n", query(1, 1, n, l));
            }
            else { // Attack
                scanf("%d %d", &l, &r);
                //cool_down(1, 1, n);
                if (l > r) {tmp = l; l = r; r = tmp;}
                attack(1, 1, n, l, r);
                //for (i = 1; i <= n; i++)  printf("(%d)%d  ", is_cool(1, 1, n, i), query(1, 1, n, i)); printf("\n");
            }
        }
     }
    return 0;
}

/* Attack */
#include <stdio.h>
#include <string.h>

#define MAXN (20000+100)
int cool[MAXN], cnt[MAXN];
int t, n, q;

void attack(int l, int r)
{
    int i;
    for (i = 1; i <= n; i++ ) { //  use many times
        if (cool[i]) cool[i]--;
        if (l <= i && i <= r) {
            if (0 == cool[i]) cool[i] = t;
            else cnt[i]++;
        }
    }
    //for (i = 1; i <= n; i++ ) printf("(%d)%d ", cool[i], cnt[i]); printf("\n");
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
        memset(cool, 0, sizeof(cool[0])*(1+n));
        memset(cnt, 0, sizeof(cnt[0])*(1+n));
        while (q--) {
            scanf("%s", cmd);
            if (cmd[0] == 'Q') { // Query
                scanf("%d", &l);
                printf("%d\n", cnt[l]);
            }
            else { // Attack
                scanf("%d %d", &l, &r);
                if (l > r) {tmp = l; l = r; r = tmp;}
                attack(l, r);
            }
        }
     }
    return 0;
}

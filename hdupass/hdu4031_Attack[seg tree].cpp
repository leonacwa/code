/* hdu 4031 Attack */
#include <stdio.h>
#include <string.h>

#define MAXN (20000+1)
typedef struct _Attack {
    int l, r;
} Attack;
Attack a[MAXN];
int a_cnt;
int pos[MAXN], def[MAXN];

int T[MAXN*6];
int n, q, t;

void build_tree()
{
    memset(T, 0, sizeof(T));
}

void attack(int x, int left, int right, int l, int r)
{
    if (r < left || right < l) return;
    if (left == right || (l <= left && right <= r)) {
        T[x]++;
    }
    else {
        int mid = left + (right - left) / 2;
        attack(x+x, left, mid, l, r);
        attack(x+x+1, mid+1, right, l, r);
    }
}

int query(int x, int left, int right, int lr)
{
    if (lr < left || right < lr) return 0;
    if (left == right) {
        return T[x];
    }
    else {
        int mid = left + (right - left) / 2;
        return T[x] + query(x+x, left, mid, lr) + query(x+x+1, mid+1, right, lr);
    }
}

int main()
{
    int cs, tt;
    int i, l, r, tmp;
    char cmd[16];

    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        build_tree();
        a_cnt = 0;
        memset(pos, 0, sizeof(pos));
        memset(def, 0, sizeof(def));

        printf("Case %d:\n", cs);
        scanf("%d %d %d", &n, &q, &t);

        while (q--) {
            scanf("%s", cmd);
            if (cmd[0] == 'Q') { // Query
                scanf("%d", &l);
                for (i = pos[l]; i < a_cnt; i++) {
                    if (a[i].l <= l && l <= a[i].r) {
                        def[l]++;
                        pos[l] = i+t;
                        i += t-1;
                    }
                }
                printf("%d\n", query(1, 1, n, l) - def[l]);
            }
            else { // Attack
                scanf("%d %d", &l, &r);
                if (l > r) {tmp = l; l = r; r = tmp;}
                a[a_cnt].l = l;
                a[a_cnt++].r = r;
                attack(1, 1, n, l, r);
            }
        }
     }
    return 0;
}

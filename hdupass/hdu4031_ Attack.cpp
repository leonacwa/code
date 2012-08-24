/* hdu 4031 Attack */
/* 感谢 QQ:530540836 HNU_herowei 大牛的指导 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;

#define MAXN (20000+1)
typedef struct _Attack {
    int l, r;
} Attack;
Attack a[MAXN];
int c[MAXN], pos[MAXN], def[MAXN];
int n, q, t, a_cnt;

#define lowbit(x) ((x)&(-(x)))

void add(int x, int v)
{
    for ( ; x <= n; x += lowbit(x)) c[x] += v;
}

int get_sum(int x)
{
    int ret = 0;
    for (; x > 0; x -= lowbit(x)) ret += c[x];
    return ret;
}

int main()
{
    int cs, tt;
    int i, l, r, tmp;
    char cmd[16];

    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        printf("Case %d:\n", cs);
        memset(c, 0, sizeof(c));
        memset(def, 0, sizeof(def));
        memset(pos, 0, sizeof(pos));
        a_cnt = 0;
        scanf("%d %d %d", &n, &q, &t);
        while (q--) {
            scanf("%s", cmd);
            if (cmd[0] == 'Q') { // Query
                scanf("%d", &l);
                if (t == 1) {
                    puts("0");
                    continue;
                }
                for (i = pos[l]; i < a_cnt; i++) { // O(n/t) ~~ 20000/50
                    if (a[i].l <= l && l <= a[i].r) {
                        def[l]++;
                        pos[l] = i+t;
                        i += t-1;
                    }
                }
                printf("%d\n", get_sum(l) - def[l]); // 攻击次数 - 防护次数
            }
            else { // Attack // O(n*log(n))
                scanf("%d %d", &l, &r);
                if (l > r) {tmp = l; l = r; r = tmp;}
                add(l, 1);
                add(r+1, -1);
                a[a_cnt].l = l;
                a[a_cnt++].r = r;
            }
        }
     }
    return 0;
}

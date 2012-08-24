/* Attack */
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define MAXN (20000+1)
int cool[MAXN*6], cnt[MAXN*6];
bool is_all[MAXN*6];
int t, n, q;

void build_tree(int n)
{
    memset(cool, 0, sizeof(cool));
    memset(is_all, 1, sizeof(is_all));  //printf("bool %d\n", is_all[1]);
    memset(cnt, 0, sizeof(cnt));
}

void cool_down(int x, int left, int right)
{
    if (is_all[x] || cool[x] > 0) {
        if (cool[x]) cool[x]--;
        return;
    }
    if (left == right) return;
    int mid = (left+right) >> 1, Min;
    cool_down(x+x, left, mid);
    cool_down(x+x+1, mid+1, right);
    Min = min(cool[x+x], cool[x+x+1]);
    if (Min > 0) {
        cool[x] += Min;
        cool[x+x] -= Min;
        cool[x+x+1] -= Min;
    }
    is_all[x] = (cool[x+x] == cool[x+x+1]) && (is_all[x+x] && is_all[x+x+1]);
}

void attack_only(int x, int left, int right, int l, int r)
{
    if (r < left || right < l) return;
    int mid = (left+right)>>1, Min;
    if (l <= left && right <= r) {
        if (is_all[x]) {
            if (cool[x] > 0) cnt[x]++;
            else cool[x] = t;
        } else {
            if (cool[x] > 0) cnt[x]++;
            else {
                attack_only(x+x, left, mid, l, r);
                attack_only(x+x+1,  mid+1, right, l, r);
                Min = min(cool[x+x], cool[x+x+1]);
                cool[x] += Min;
                cool[x+x] -= Min;
                cool[x+x+1] -= Min;
                is_all[x] = (cool[x+x] == cool[x+x+1]) && (is_all[x+x] && is_all[x+x+1]);
            }
        }
        return;
    }
    cool[x+x] += cool[x];
    cool[x+x+1] += cool[x];
    cool[x] = 0;
    attack_only(x+x, left, mid, l, r);
    attack_only(x+x+1, mid+1, right, l, r);
    Min = min(cool[x+x], cool[x+x+1]);
    cool[x+x] -= Min;
    cool[x+x+1] -= Min;
    cool[x] += Min;
    is_all[x] = (cool[x+x] == cool[x+x+1]) && (is_all[x+x] && is_all[x+x+1]);
}

void cool_attack(int x, int left, int right, int l, int r)
{
    if (r < left || right < l) {
        cool_down(x, left, right);
        return;
    }
    int mid = (left+right)>>1, Min;
    if (l <= left && right <= r) {
        if (left == right) {  // Node
            if (cool[x] > 0) cool[x]--;
            if (cool[x] > 0)  cnt[x]++;
            else cool[x] = t;
            return;
        }
        if (cool[x] == 0 && !is_all[x]) {
            cool_attack(x+x, left, mid, l, r);
            cool_attack(x+x+1, mid+1, right, l, r);
            Min = min(cool[x+x], cool[x+x+1]);
            cool[x] += Min;
            cool[x+x] -= Min;
            cool[x+x+1] -= Min;
            is_all[x] = (cool[x+x] == cool[x+x+1]) && (is_all[x+x] && is_all[x+x+1]);
        } else if (!is_all[x] && cool[x] == 1) {
            cool[x]--;
           //attack_only(x, left, right, l, r);
            attack_only(x+x, left, mid, l, r);
            attack_only(x+x+1, mid+1, right, l, r);
        } else {
            if (cool[x]) cool[x]--;
            if (cool[x]) cnt[x]++;
            else cool[x] = t;
        }
        return;
    }
    if (cool[x] > 0) { // 分配冷却时间, 因为攻击区间 [l, r] 不包括 [left, right]
        cool[x+x] += cool[x];
        cool[x+x+1] += cool[x];
        cool[x] = 0;
    }
    cool_attack(x+x, left, mid, l, r);
    cool_attack(x+x+1, mid+1, right, l, r);
    Min = min(cool[x+x], cool[x+x+1]);
    cool[x] += Min;
    cool[x+x] -= Min;
    cool[x+x+1] -= Min;
    is_all[x] = (cool[x+x] == cool[x+x+1]) && (is_all[x+x] && is_all[x+x+1]);
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
                cool_attack(1, 1, n, l, r);
            }
        }
     }
    return 0;
}

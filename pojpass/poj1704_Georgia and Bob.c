/* poj 1704 Georgia and Bob */
#include <stdio.h>
#include <stdlib.h>
#define MAXP 10000
#define MAXN 1000
int p[MAXN+1], st[MAXN], sts, n;

int int_cmp(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int xor_st(int x)
{
    int ret = 0, i;
    for (i = 0; i < sts; i++) if (i != x){
        ret = ret ^ st[i];
    }
    return ret;
}

int main()
{
    int i, win, tt;
    scanf("%d", &tt);
    while (tt--) {
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%d", p+i);
        }
        qsort(p, n, sizeof(int), int_cmp);
        sts = 0;
        i = 0;
        if (n%2) {
            st[sts++] = p[i++] - 0 - 1;
        }
        for (; i < n; i+=2) {
            st[sts++] = p[i+1] - p[i] - 1;
        }
        if (0 == xor_st(sts)) {
            puts("Bob will win");
        }
        else {
            for (win = 0, i = sts-1; !win && i >= 0; i--) {
                if (st[i] >= xor_st(i)) {
                    win = 1;
                }
            }
            if (win == 1) {
                puts("Georgia will win");
            }
            else {
                puts("Not sure");
            }
        }
    }
    return 0;
}

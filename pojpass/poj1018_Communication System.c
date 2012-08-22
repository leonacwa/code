/** poj 1018 Communication System */
#include <stdio.h>
#include <stdlib.h>

typedef struct _Manu{
    int b, p;
} Manu;
typedef struct _Dev{
    int ms;
    Manu m[101];
}Dev;
Dev dev[101];
int B[100*100], bs;
int n;

int int_cmp(const void *a, const void *b)
{
    return *((int*)b) - *((int*)a);
}
int manu_p_cmp(const void *a, const void *b)
{
    return ((Manu*)a)->p - ((Manu*)b)->p;
}
int search(int k, int b)
{
    if (k == n) {
        return 0;
    }
    int i;
    for (i = 0; i < dev[k].ms; i++){
        if (dev[k].m[i].b >= b) {
            return dev[k].m[i].p + search(k+1, b);
        }
    }
    return 0x00ffffff;
}
int main()
{
    int tt, i, j, p;
    double ans, t_ans;
    scanf("%d", &tt);
    while (tt--) {
        scanf("%d", &n);
        bs = 0;
        for (i = 0; i < n; i++) {
            scanf("%d", &dev[i].ms);
            for (j = 0; j < dev[i].ms; j++) {
                scanf("%d %d", &dev[i].m[j].b, &dev[i].m[j].p);
                B[bs++] = dev[i].m[j].b;
            }
            qsort(dev[i].m, dev[i].ms, sizeof(Manu), manu_p_cmp);
        }
        qsort(B, bs, sizeof(int), int_cmp);
        j = B[0] - 1;
        ans = 0;
        for (i = 0; i < bs; i++) {
            if (B[i] == j) {
                continue;
            }
            j = B[i];
            p = search(0, j);
            t_ans = (double)j / p;
            if (ans < t_ans) {
                ans = t_ans;
            }
            //printf("B:%d P:%d\n", j, p);
        }
        printf("%.3f\n", ans);
    }
    return 0;
}

/* ZOJ 3529 A Game Between Alice and Bob */
/* 关键是转换为 Nim 博弈*/
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN (100000+1)
#define MAX_NUM (5000000+1)

int a[MAX_NUM], cnt[MAXN];
int n;

void init()
{
    int i, j, sq = (int)sqrt(MAX_NUM);
    for (i = 2; i < MAX_NUM; i++) {
        if (a[i] == 0) a[i] = 1;
        for (j = i+i; j < MAX_NUM; j += i) {
            if (a[j] < a[i]+1) {
                a[j] = a[i]+1;
            }
        }
    }
}

int main()
{
    int i, cs = 0, res, tmp, num;
    init();
    while (~scanf("%d", &n)) {
        cs++;
        res = 0;
        for (i = 0; i < n; i++) {
            scanf("%d", &num);
            cnt[i] = a[num];
            res ^= cnt[i];
        }
        if (res == 0) {
            printf("Test #%d: Bob\n", cs);
            continue;
        }
        for (i = 0; i < n; i++) {
            tmp = res ^ cnt[i];
            if (cnt[i] >= tmp) break;
        }
        if (i == n) printf("Test #%d: Bob\n", cs);
        else printf("Test #%d: Alice %d\n", cs, i+1);
    }
    return 0;
}

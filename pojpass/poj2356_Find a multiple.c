/* poj 2356 Find a multiple */
/// 鸽巢原理
#include <stdio.h>
#include <string.h>
#define MAXN (10000+5)
int a[MAXN], l[MAXN];

int main()
{
    int i, j, n, s, find;
while (1 == scanf("%d", &n)) {
    memset(l, -1, sizeof(l));
    l[0] = 0;
    s = 0;
    find = 0;
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s = (s+a[i]) % n;
        if (l[s] >= 0 && !find) {
            printf("%d\n", i - l[s]);
            for (j = l[s]+1; j <= i; j++) {
                printf("%d\n", a[j]);
            }
            find = 1;
        }
        l[s] = i;
    }
    if (!find) {
        puts("0");
    }
    return 0;
}
}

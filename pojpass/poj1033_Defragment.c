/*poj 1033 Defragment */
#include <stdio.h>
#include <string.h>
#define MAXN (10000+1)
int f[MAXN], d[MAXN];
int n, k, fs;
int main()
{
    int i, j, t, op, counter;
    scanf("%d %d", &n, &k);
    memset(d, -1, sizeof(d));
    memset(f, -1, sizeof(f));
    op = 1;
    counter = 0;
    for (i = 0; i < k; i++) {
        scanf("%d", &fs);
        for (j = 0; j < fs; j++) {
            scanf("%d", &f[counter]);
            f[counter]--;
            d[f[counter]] = counter;
            op = (op && f[counter] == counter);
            counter++;
        }
    }
    if (!op) {
        for (i = 0; i < counter; i++) {
            if (f[i] == i || f[i] == -1) {
                continue;
            }
            if (d[i] == -1) { /// 单链
                for (j = i; -1 != f[j] && j != f[j]; ) {
                    printf("%d %d\n", f[j] +1, j +1);
                    d[j] = j;
                    d[f[j]] = -1;
                    t = f[j];
                    f[j] = j;
                    j = t;
                }
            } /*
            else { /// 环
                for (t = n-1; t >= 0; t--) {
                    if (d[t] == -1)  break;
                }
                printf("%d %d\n", i +1, t+1);
                d[t] = d[i];
                f[d[t]] = t;
                d[i] = -1;
                i--;
            } */
        }
        /* */
        for (i = 0; i < counter; i++) {
            if (f[i] == i || f[i] == -1) {
                continue;
            }
            if (d[i] != i) { /// 环
                for (t = n-1; t >= 0; t--) {
                    if (d[t] == -1)  break;
                }
                printf("%d %d\n", i +1, t+1);
                d[t] = d[i];
                f[d[t]] = t;
                d[i] = -1;
                for (j = i; -1 != f[j] && j != f[j]; ) {
                    printf("%d %d\n", f[j] +1, j +1);
                    d[j] = j;
                    d[f[j]] = -1;
                    t = f[j];
                    f[j] = j;
                    j = t;
                }
            }
        }
        /**/
    }
    else {
        puts("No optimization needed");
    }
    return 0;
}

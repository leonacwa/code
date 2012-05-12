/** poj 1029 False coin */
#include <stdio.h>
#include <string.h>

#define MAXN (1000+1)
typedef struct _Test{
    int p, l[MAXN], r[MAXN];
    char rs;
}Test;

Test ts[100];
char fc[MAXN];

int main()
{
    int n, k, p, t, i, j, false_coin;

//while (!feof(stdin))
{

    memset(fc, 0, sizeof(fc));
    memset(ts, 0, sizeof(ts));
    scanf("%d %d\n", &n, &k);
    for (i = 0; i < k; i++) {
        scanf("%d ", &ts[i].p);
        for (j = 0; j < ts[i].p; j++) {
            scanf("%d ", &t);
            ts[i].l[t] = 1;
        }
        for (j = 0; j < ts[i].p; j++) {
            scanf("%d ", &t);
            ts[i].r[t] = 1;
        }
        scanf("%c\n", &ts[i].rs);
        if (ts[i].rs == '=') {
            for (j = 1; j <= n; j++) if (1 == ts[i].l[j] || 1 == ts[i].r[j]){
                fc[j] = 1;
            }
        }
        else {
            for (j = 1; j <= n; j++) if (0 == ts[i].l[j] && 0 == ts[i].r[j]){
                fc[j] = 1;
            }
        }
    }
    false_coin = 0;
    for (i = 2; i <= 1+2*n; i++) {
        if (fc[i/2] == 1) {
            i++;
            continue;
        }
        //printf("Maybe False Coin:%d\n", i/2);
        for (j = 0; j < k; j++) {
            if (ts[j].rs == '>') {
                if ((0==i%2 && ts[j].l[i/2]) || (1==i%2 && ts[j].r[i/2])) {
                    break;
                }
            }
            else if (ts[j].rs == '<') {
                if ((1==i%2 && ts[j].l[i/2]) || (0==i%2 && ts[j].r[i/2])) {
                    break;
                }
            }
        }
        if (j < k && i%2) { /// final test and unaccept
            fc[i/2] = 1;
        }
        else if (j == k){ /// accpt all test
            if (0 != false_coin && false_coin != i / 2) {
                false_coin = 0;
                break;
            }
            else {
                false_coin = i / 2;
            }
        }
    }
    printf("%d\n", false_coin);
}
    return 0;
}

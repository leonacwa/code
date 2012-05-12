/** poj 1026 Cipher */
#include <stdio.h>
#include <string.h>
#define MAXN 256
char msg[MAXN], ans[MAXN];
int a[MAXN];
int q[MAXN][MAXN], ql[MAXN];
int n, k;

int main()
{
    int i, j, lm;
    while (scanf("%d", &n) && n != 0) {
        for (i = 0; i < n; i++) {
            scanf("%d", a+i);
            a[i]--;
        }
        for (i = 0; i < n; i++) {
            q[i][0] = i;
            ql[i] = 1;
            for (j = a[i]; j != i; j = a[j]) {
                q[i][ql[i]++] = j;
            }
        }
        while (scanf("%d", &k) && k != 0) {
            getchar();
            gets(msg);
            lm = strlen(msg);
            while (lm < n) {
                msg[lm++] = ' ';
            }
            msg[n] = '\0';
            for (i = 0; i < n; i++) {
                ans[q[i][k%ql[i]]] = msg[i];
            }
            ans[n] = '\0';
            puts(ans);
        }
        puts("");
    }
    return 0;
}

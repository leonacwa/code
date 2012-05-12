/* poj3373 Changing Digits */
#include <stdio.h>
#include <string.h>
#define MAXN 101
int rm[MAXN][7][10000];
char sn[MAXN], ans[MAXN];
int k, n, minp;

void dfs(int x, int m, int res)
{
    char t, c;
    if (x >= n) {
        if (res == 0 && m < minp) {
            minp = m;
            strcpy(ans, sn);
        }
        return;
    }
    if (m >= minp) {
        return;
    }
    if (rm[x][m][res]) {
        return;
    }
    rm[x][m][res] = 1;
    t = sn[x];
    if (x != 0) {
        sn[x] = '0';
        if (t != sn[x]) {
            dfs(x+1, m+1, (res*10) % k);
        }
        else {
            dfs(x+1, m, (res*10) % k);
        }
    }

    for (c = '1'; c <= '9'; c++) {
        sn[x] = c;
        if (t != sn[x]) {
            dfs(x+1, m+1, (res*10+c-'0') % k);
        }
        else {
            dfs(x+1, m, (res*10+c-'0') % k);
        }
    }
    sn[x] = t;
}
int main()
{
    while (gets(sn) && ~scanf("%d\n", &k)) {
        memset(rm, 0, sizeof(rm));
        n = strlen(sn);
        ans[n] = 0;
        minp = 6; /// 由鸽巢原理得到
        dfs(0, 0, 0);
        printf("%s\n", ans);
    }
   return 0;
}

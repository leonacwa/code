/** poj 1020 Anniversary Cake */
#include <stdio.h>
#include <string.h>
int s, n, side[11], col[40];
int dfs(int k)
{
    int i, c, r, j;
    if (k == n){
        return 1;
    }
    for (i = 0, c = r = s+1; i < s; i++) {
        if (r > col[i]) {
            r = col[i];
            c = i;
        }
    }
    for (i = 10; i >= 1; i--){
        if (side[i] > 0 && r+i <= s && c+i <= s) {
            for (j = c; j < c+i; j++) {
                if (col[j] > r) {
                    break;
                }
            }
            if (j == c+i) {
                for (j = c; j < c+i; j++) {
                    col[j] += i;
                }
                side[i]--;
                if (dfs(k+1)) {
                    return 1;
                }
                side[i]++;
                for (j = c; j < c+i; j++) {
                    col[j] -= i;
                }
            }
        }
    }
    return 0;
}
int main()
{
    int tt, i, area, t;
    scanf("%d", &tt);
    while (tt--) {
        memset(side, 0, sizeof(side));
        memset(col, 0, sizeof(col));
        scanf("%d %d", &s, &n);
        area = 0;
        for (i = 0; i < n; i++) {
            scanf("%d", &t);
            side[t]++;
            area += t * t ;
        }
        if (s*s == area && dfs(0)) {
            puts("KHOOOOB!");
        }
        else {
            puts("HUTUTU!");
        }
    }
    return 0;
}

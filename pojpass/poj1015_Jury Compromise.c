/**poj 1015 Jury Compromise */
#include <stdio.h>
#include <string.h>
#define ZERO 400
int f[201][21][802], path[201][21][802];
int d[201], p[201];
int n, m;

void p_ans(int n, int m, int k)
{
    if (n == 0)
        return;
    if (path[n][m][ZERO+k] == n) {
        p_ans(n-1, m-1, k-(d[n]-p[n]));
        printf("%d ", n);
    }
    else {
        p_ans(n-1, m, k);
    }
}

int main()
{
    int i, j, k, cnt, c, h, b, e;
    for (cnt = 1; 2 ==scanf("%d %d", &n, &m) && n && m; cnt++) {
        for (i = 1; i <= n; i++) {
            scanf("%d %d", p+i, d+i);
        }
        memset(f, 0xff, sizeof(f));
        b = -20 * m;
        e = 20 * m;
        path[0][0][ZERO] = 0;
        for (i = 1; i <= n; i++) {
            f[i-1][0][ZERO] = 0;
            for (j = 1; j <= m && j <= i; j++) {
                c = d[i] - p[i];
                h = d[i] + p[i];
                for (k = b; k <= e; k++) {
                    if (b <= k-c && k-c <= e) {
                        if (f[i-1][j][ZERO+k] != -1) {
                            f[i][j][ZERO+k] = f[i-1][j][ZERO+k];
                            path[i][j][ZERO+k] = -1;
                        }
                        if ((f[i-1][j-1][ZERO+k-c] != -1)
                          &&(f[i][j][ZERO+k] == -1 || f[i][j][ZERO+k] < f[i-1][j-1][ZERO+k-c]+h)) {
                            f[i][j][ZERO+k] = f[i-1][j-1][ZERO+k-c]+h;
                            path[i][j][ZERO+k] = i;
                        }
                    }
                }
            }
        }
        for (i = 0; i <= e; i++) {
            if (f[n][m][ZERO+i] > f[n][m][ZERO-i]) {
                break;
            }
            else if (f[n][m][ZERO-i] != -1){
                i = -i;
                break;
            }
        }
        printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n",
               cnt, (f[n][m][ZERO+i]-i)/2, (f[n][m][ZERO+i]+i)/2);
        p_ans(n, m, i);
        printf("\n");
    }
    return 0;
}

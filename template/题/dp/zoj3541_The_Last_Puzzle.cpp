/* zoj 3541 The Last Puzzle
关键：要保证最优，hero每次按下的是一个区间。
记住这个DP方程，是一个经典的模型。
*/
#include <stdio.h>
#include <string.h>
#define MAXN 201

int f[MAXN][MAXN][2];
int go[MAXN][MAXN][2];
int d[MAXN], t[MAXN];

bool opt(int &a, int b)
{
    if (a == -1 || a > b) {
        a = b;
        return true;
    }
    return false;
}

void print(int i, int j, int to)
{
    if (i == j) {
        printf("%d", i+1);
    }
    else if (to == 0) {
        printf("%d ", i+1);
        print(i+1, j, go[i][j][0]);
    }
    else {
        printf("%d ", j+1);
        print(i, j-1, go[i][j][1]);
    }
}

int main()
{
    int i, j, k, to, ans, n;
    while (1 == scanf("%d", &n)) {
        for (i = 0; i < n; i++) scanf("%d", t+i);
        for (i = 0; i < n; i++) scanf("%d", d+i);
        for (i = 0; i < n; i++) f[i][i][0] = f[i][i][1] = go[i][i][0] = go[i][i][1] = 0;
        for (k = 2; k <= n; ++k) {
            for (i = 0; (j=i+k-1) < n; ++i) {
                f[i][j][0] = f[i][j][1] = -1;
                if (f[i+1][j][0] != -1 && opt(f[i][j][0], f[i+1][j][0] + d[i+1] - d[i])) go[i][j][0] = 0;
                if (f[i+1][j][1] != -1 && opt(f[i][j][0], f[i+1][j][1] + d[j] - d[i])) go[i][j][0] = 1;
                if (f[i][j-1][1] != -1 && opt(f[i][j][1], f[i][j-1][1] + d[j] - d[j-1])) go[i][j][1] = 1;
                if (f[i][j-1][0] != -1 && opt(f[i][j][1], f[i][j-1][0] + d[j] - d[i])) go[i][j][1] = 0;
                if (f[i][j][0] >= t[i]) f[i][j][0] = -1;
                if (f[i][j][1] >= t[j]) f[i][j][1] = -1;
            }
        }
        ans = f[0][n-1][0];
        to = 0;
        if (ans == -1 || (f[0][n-1][1] != -1 && ans > f[0][n-1][1])) {
            ans = f[0][n-1][1];
            to = 1;
        }
        if (ans == -1) printf("Mission Impossible\n");
        else print(0, n-1, to), puts("");
    }
    return 0;
}

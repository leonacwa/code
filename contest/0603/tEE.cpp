#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 17;

int n, Max;
int dom[MAXN][2];
int M[MAXN][MAXN][2];
bool used[MAXN];
bool mat[MAXN][MAXN][2];
struct XY {
    int x, y, z;
} xy[MAXN * MAXN * 2];
int cnt;

void __PushXY(int x, int y, int z)
{
    if (x <= 0 || x >= MAXN || y <= 0 || y >= MAXN) return;
    xy[cnt].x = x;
    xy[cnt].y = y;
    xy[cnt].z = z;
    mat[x][y][z] = true;
    ++cnt;
}

void PushXY(int x, int y, int z)
{
    if (z == 0) {
        __PushXY(x, y, 1);
        __PushXY(x, y-1, 1);
        __PushXY(x-1, y, 1);
    } else {
        __PushXY(x, y, 0);
        __PushXY(x, y+1, 0);
        __PushXY(x+1, y, 0);
    }
}

void PopXY()
{
    if (cnt > 0) {
        --cnt;
        int x = xy[cnt].x, y = xy[cnt].y, z = xy[cnt].z;
        //mat[x][y][z] = false;
    }
}

bool can(int d, int x, int y, int z)
{
    if (M[x][y][z]) return false;
    bool ret = false;
    if (z == 0) {
        ret = (M[x][y-1][1] == d || M[x-1][y][1] == d || M[x][y][1] == d) &&
               ((M[x][y-1][1] == d || M[x][y-1][1] == 0) && (M[x-1][y][1] == d || M[x-1][y][1] == 0) &&
                (M[x][y][1] == d || M[x][y][1] == 0));
    } else {
        ret = (M[x][y][0] == d || M[x+1][y][0] == d || M[x][y+1][0] == d) &&
               ((M[x][y][0] == d || M[x][y][0] == 0) && (M[x+1][y][0] == d || M[x+1][y][0] == 0) &&
                (M[x][y+1][0] == d || M[x][y+1][0] == 0));
    }
    return ret;
}

int count(int d, int x, int y, int z)
{
    if (M[x][y][z] != d) return 0;
    int ret = 0;
    if (z == 0) {
        ret = (M[x][y-1][1] == d) + (M[x-1][y][1] == d)  + (M[x][y][1] == d);
    } else {
        ret = (M[x][y][0] == d) + (M[x+1][y][0] == d) + (M[x][y+1][0] == d);
    }
    return ret;
}

void dfs(int res, int sum)
{
    if (Max < sum) Max = sum;
    //if (res <= 0) return;
    if (res > n) return;
    for (int i = res; i == res; ++i) {
        if (used[i]) continue;
        used[i] = true;
        for (int j = 0; j < cnt; ++j) {
            int x = xy[j].x, y = xy[j].y,z = xy[j].z;
            if (mat[x][y][z]) continue;
            for (int k = 0; k < 2; ++k) {
                int a = dom[i][k], b = dom[i][1 - k];
                if (z == 0 && can(a, x, y, 0)) {
                    M[x][y][0] = b;
                    if (can(b, x, y, 1)) {
                        M[x][y][0] = a;
                        M[x][y][1] = b;
                        PushXY(x, y, 1);
                        int t = count(a, x, y, 0) + count(b, x, y, 1) - (a==b)*2;
                        dfs(res+1, sum + t);
                        M[x][y][0] = b;
                        M[x][y][1] = 0;
                        PopXY();
                    }
                    if (can(b, x, y-1, 1)) {
                        M[x][y][0] = a;
                        M[x][y-1][1] = b;
                        PushXY(x, y-1, 1);
                        int t = count(a, x, y, 0) + count(b, x, y-1, 1) - (a==b)*2;
                        dfs(res+1, sum + t);
                        PopXY();
                        M[x][y][0] = b;
                        M[x][y-1][1] = 0;
                    }
                    if (can(b, x-1, y, 1)) {
                        M[x][y][0] = a;
                        M[x-1][y][1] = b;
                        PushXY(x-1, y, 1);
                        int t = count(a, x, y, 0) + count(b, x-1, y, 1) - (a==b) * 2;
                        dfs(res+1, sum + t);
                        PopXY();
                        M[x][y][0] = b;
                        M[x-1][y][1] = 0;
                    }
                    M[x][y][0] = 0;
                }
                if (z == 1 && can(a, x, y, 1)) {
                    M[x][y][1] = b;
                    if (can(b, x, y, 0)) {
                        M[x][y][1] = a;
                        M[x][y][0] = b;
                        PushXY(x, y, 0);
                        int t = count(a, x, y, 1) + count(b, x, y, 0) - (a==b) * 2;
                        dfs(res+1, sum + t);
                        M[x][y][1] = b;
                        M[x][y][0] = 0;
                        PopXY();
                    }
                    if (can(b, x+1, y, 0)) {
                        M[x][y][1] = a;
                        M[x+1][y][0] = b;
                        int t = count(a, x, y, 1) + count(b, x+1, y, 0) - (a==b) * 2;
                        PushXY(x+1, y, 0);
                        dfs(res+1, sum + t);
                        PopXY();
                        M[x][y][1] = b;
                        M[x+1][y][0] = 0;
                    }
                    if (can(b, x, y+1, 0)) {
                        M[x][y][1] = a;
                        M[x][y+1][0] = b;
                        int t = count(a, x, y, 1) + count(b, x, y+1, 0) - (a==b) * 2;
                        PushXY(x, y+1, 0);
                        dfs(res+1, sum + t);
                        PopXY();
                        M[x][y][1] = b;
                        M[x][y+1][0] = 0;
                    }
                    M[x][y][1] = 0;
                }
            }
        }
        used[i] = false;
    }
}

int main()
{
    freopen("data.in", "r", stdin);
    int nCase = 0;
    while (EOF != scanf("%d", &n) && n > 0) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &dom[i][0], &dom[i][1]);
        }
        memset(M, 0, sizeof(M));
        memset(used, 0, sizeof(used));
        memset(mat, 0, sizeof(mat));
        cnt = 0;
        Max = 0;
        int x, y;
        x = y = MAXN / 2;
        used[1] = true;
        for (int k = 0; k < 2; ++k) {
            int a = dom[1][k], b = dom[1][1-k];
            int res = 2;
            //1
            M[x][y][0] = a;
            PushXY(x, y, 0);

            M[x][y][1] = b;
            PushXY(x, y, 1);
            dfs(res, 0);
            M[x][y][1] = 0;
            PopXY();
            //2
            M[x][y-1][1] = b;
            PushXY(x, y-1, 1);
            dfs(res, 0);
            M[x][y-1][1] = 0;
            PopXY();
            //3
            M[x-1][y][1] = b;
            PushXY(x-1, y, 1);
            dfs(res, 0);
            M[x-1][y][1] = 0;
            PopXY();

            PopXY();

            //4
            M[x][y][1] = a;
            PushXY(x, y, 1);

            M[x][y+1][0] = b;
            PushXY(x, y+1, 0);
            dfs(res, 0);
            PopXY();
            M[x][y+1][0] = 0;
            //5
            M[x+1][y][0] = b;
            PushXY(x+1, y, 0);
            dfs(res, 0);
            PopXY();
            M[x+1][y][0] = 0;

            PopXY();
        }

        printf("%2d:", ++nCase);
        printf("%d\n", Max);
    }
    return 0;
}

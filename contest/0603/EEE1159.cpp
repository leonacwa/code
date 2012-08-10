#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 15;

int n, Max;
int dom[MAXN][2];
struct Dom {int l, r; } rdom[MAXN];
int M[MAXN][MAXN][2];
bool used[MAXN];

bool cmp(const Dom A, const Dom B) {
    if (A.l != B.l) return A.l < B.l;
    return A.r < B.r;
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
bool test(int x, int y, int z)
{
    bool ret = false;
    if (z == 0) {
        ret = ((M[x][y-1][1] == 0) && (M[x-1][y][1] == 0) &&
                (M[x][y][1] == 0));
    } else {
        ret = ((M[x][y][0] == 0) && (M[x+1][y][0] == 0) &&
                (M[x][y+1][0] == 0));
    }
    return ret;
}

void dfs(int res, int sum)
{
    if (Max < sum) Max = sum;
    if (res > n) return;
    for (int i = res; i == res; ++i) {
        //if (used[i]) continue;
        used[i] = true;
        for (int x = 1; x < MAXN-1; ++x) for (int y = 1; y < MAXN-1; ++y) {
            if (M[x][y][0] && M[x][y][1]) continue;
            if (test(x, y, 0) && test(x, y, 1)) continue;
            for (int k = 0; k < 2; ++k) {
                int a = dom[i][k], b = dom[i][1 - k];
                if (can(a, x, y, 0)) {
                    M[x][y][0] = b;
                    if (can(b, x, y, 1)) {
                        M[x][y][0] = a;
                        M[x][y][1] = b;
                        int t = count(a, x, y, 0) + count(b, x, y, 1) - (a==b)*2;
                        dfs(res+1, sum + t);
                        M[x][y][0] = b;
                        M[x][y][1] = 0;
                    }
                    if (can(b, x, y-1, 1)) {
                        M[x][y][0] = a;
                        M[x][y-1][1] = b;
                        int t = count(a, x, y, 0) + count(b, x, y-1, 1) - (a==b)*2;
                        dfs(res+1, sum + t);
                        M[x][y][0] = b;
                        M[x][y-1][1] = 0;
                    }
                    if (can(b, x-1, y, 1)) {
                        M[x][y][0] = a;
                        M[x-1][y][1] = b;
                        int t = count(a, x, y, 0) + count(b, x-1, y, 1) - (a==b) * 2;
                        dfs(res+1, sum + t);
                        M[x][y][0] = b;
                        M[x-1][y][1] = 0;
                    }
                    M[x][y][0] = 0;
                }
                if (can(a, x, y, 1)) {
                    M[x][y][1] = b;
                    if (can(b, x, y, 0)) {
                        M[x][y][1] = a;
                        M[x][y][0] = b;
                        int t = count(a, x, y, 1) + count(b, x, y, 0) - (a==b) * 2;
                        dfs(res+1, sum + t);
                        M[x][y][1] = b;
                        M[x][y][0] = 0;
                    }
                    if (can(b, x+1, y, 0)) {
                        M[x][y][1] = a;
                        M[x+1][y][0] = b;
                        int t = count(a, x, y, 1) + count(b, x+1, y, 0) - (a==b) * 2;
                        dfs(res+1, sum + t);
                        M[x][y][1] = b;
                        M[x+1][y][0] = 0;
                    }
                    if (can(b, x, y+1, 0)) {
                        M[x][y][1] = a;
                        M[x][y+1][0] = b;
                        int t = count(a, x, y, 1) + count(b, x, y+1, 0) - (a==b) * 2;
                        dfs(res+1, sum + t);
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
            scanf("%d%d", &rdom[i].l, &rdom[i].r);
            //if (rdom[i].l > rdom[i].r) swap(rdom[i].l, rdom[i].r);
        }
        sort(rdom+1, rdom + n+1, cmp);
        int a[MAXN] = {1, 2, 3, 4, 5, 6, 7, 8};
        memset(M, 0, sizeof(M));
        memset(used, 0, sizeof(used));
        Max = 0;
        do {
            for (int i = 1; i <= n; ++i) {
                dom[i][0] = rdom[a[i-1]].l, dom[i][1] = rdom[a[i-1]].r;
            }
            int x, y;
            x = y = MAXN / 2;
            used[1] = true;
            for (int i = 1; i < n; ++i) {
                for (int k = 0; k < 2; ++k) {
                    int a = dom[i][k], b = dom[i][1-k];
                    int res = i + 1;
                    //1
                    M[x][y][0] = a;

                    M[x][y][1] = b;
                    dfs(res, 0);
                    M[x][y][1] = 0;
                    //2
                    M[x][y-1][1] = b;
                    dfs(res, 0);
                    M[x][y-1][1] = 0;
                    //3
                    M[x-1][y][1] = b;
                    dfs(res, 0);
                    M[x-1][y][1] = 0;

                    M[x][y][0] = 0;

                    //4
                    M[x][y][1] = a;

                    M[x][y+1][0] = b;
                    dfs(res, 0);
                    M[x][y+1][0] = 0;
                    //5
                    M[x+1][y][0] = b;
                    dfs(res, 0);
                    M[x+1][y][0] = 0;

                    M[x][y][1] = 0;
                }
            }
        } while (next_permutation(a, a+n));
        printf("%2d:", ++nCase);
        printf("%d\n", Max);
    }
    return 0;
}

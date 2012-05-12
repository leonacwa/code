/** poj 1021 2D-Nim */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _TPoint{
    int x, y;
}TPoint;
typedef struct _TBlock{
    int ps, id, hash;
}TBlock;

int step[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
TPoint p[100*100];
TBlock b[2][100*100];
int cnt[2];
int board[101][101];
int xx[100*100], yy[100*100], ps;
int W, H, n;

int block_cmp(const void*a, const void *b)
{
    return ((TBlock*)a)->hash - ((TBlock*)b)->hash;
}
int block_dfs(int x, int y, int ID)
{
    int i, ret = 0;
    if (x < 0 || x >= W || y < 0 || y >= H || board[y][x] != -2) {
        return 0;
    }
    board[y][x] = ID;
    xx[ps] = x;
    yy[ps] = y;
    ps++;
    ret++;
    for (i = 0; i < 4; i++) {
        ret += block_dfs(x+step[i][0], y+step[i][1], ID);
    }
    return ret;
}
int main()
{
    int tt, bi, i, j, k, t, yes;
    scanf("%d", &tt);
    while (tt--) {
        scanf("%d %d %d", &W, &H, &n);
        for (bi = 0; bi < 2; bi++) {
            memset(board, -1, sizeof(board));
            for (i = 0; i < n; i++) {
                scanf("%d %d", &p[i].x, &p[i].y);
                board[p[i].y][p[i].x] = -2;
            }
            cnt[bi] = 0;
            for (i = 0; i < n; i++) {
                if ( board[p[i].y][p[i].x] == -2) {
                    ps = 0;
                    b[bi][cnt[bi]].ps = block_dfs(p[i].x, p[i].y, cnt[bi]);
                    b[bi][cnt[bi]].id = cnt[bi];
                    t = 0;
                    for (j = 0; j < ps-1; j++) {
                        for (k = j+1; k < ps; k++){
                            t += (xx[j]-xx[k])*(xx[j]-xx[k]) + (yy[j]-yy[k])*(yy[j]-yy[k]);
                        }
                    }
                    b[bi][cnt[bi]].hash = t;
                    cnt[bi]++;
                }
            }
            qsort(b[bi], cnt[bi], sizeof(TBlock), block_cmp);
        }
        yes = cnt[0] == cnt[1];
        for (i = 0; yes &&i < cnt[0]; i++) {
            yes = b[0][i].hash == b[1][i].hash;
        }
        puts(yes?"YES":"NO");
    }
    return 0;
}

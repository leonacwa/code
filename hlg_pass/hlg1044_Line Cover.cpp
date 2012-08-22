/* Line Cover */
#include <stdio.h>
#include <string.h>

#define MAXN 201
#define MAX_LINES 5

typedef struct _Point{
    int x, y;
} Point;
Point p[MAXN], list[MAXN];
int n, n2, best;
int g[32][32];

int cross(Point a, Point b, Point o) /* 叉积 */
{
    return (a.x - o.x)*(b.y - o.y) - (a.y - o.y)*(b.x - o.x);
}

int clear_point() /* 百万的时间复杂度， O(n^3), n <= 200*/
{
    int i, j, k, lines = 0;
    int pl[MAXN], count;
    char vis[MAXN] = {0};

    for (i = 0; i < n-1; i++) if (!vis[i]) {
        pl[0] = i;
        for (j = i+1; j < n; j++) if (!vis[j]) {
            pl[1] = j;
            count = 2;
            for (k = j+1; k < n; k++) if (!vis[k]) {
                if (0 == cross(p[i], p[j], p[k])) {
                    pl[count++] = k;
                }
            }
            if (count > MAX_LINES) {
                lines++;
                if (lines > MAX_LINES) return lines;
                for (k = 0; k < count; k++) {
                    vis[pl[k]] = 1;
                }
                break;
            }
        }
    }
    n2 = 0;
    for (i = 0; i < n; i++) {
        if (!vis[i]) list[n2++] = p[i];
    }
    return lines;
}

void pre_work() /* O(25*25*25) , 先算出i和j线上的点，为dfs优化 */
{
    int i, j, k;
    memset(g, 0, sizeof(g));
    for (i = 0; i < n2; i++) {
        for (j = 0; j < n2; j++) if (i != j) {
            g[i][j] |= (1 << i) | (1 << j);
            for (k = 0; k < n2; k++) if (k != i && k != j){
                if (0 == cross(list[i], list[j], list[k])) {
                    g[i][j] |= (1 << k);
                }
            }
            g[j][i] = g[i][j];
        }
    }
}

void dfs(int cur, int lines, int ss)
{
    int i, j, only_one;
    if (lines >= best) return;
    if (ss == (1<<n2)-1) {
        if (best > lines) best = lines;
        return;
    }
    if (ss & (1<<cur)) dfs(cur+1, lines, ss);
    else {
        only_one = 1;
        for (i = cur+1; i < n2; i++) {
            if (0 == (ss & (1<<i))) {
                only_one = 0;
                dfs(cur+1, lines+1, ss | g[cur][i]);
            }
        }
        if (only_one && lines+1 < best) best = lines+1;
    }
}

int main()
{
    int tt, i, flag, lines;
    scanf("%d", &tt);
    while (tt--) {
        scanf("%d", &n);
        for (i = 0; i < n; i++)  scanf("%d %d", &p[i].x, &p[i].y);
        flag = 0;
        lines = clear_point();
        if (lines > MAX_LINES || (lines == MAX_LINES && n2 > 0) || n2 > 5*(MAX_LINES-lines)) {
            flag = 1;
        }
        else if (n2 == 0) {
            best = 0;
        }
        else {
            pre_work();
            best = MAX_LINES - lines + 1;
            dfs(0, 0, 0);
            if (best + lines > MAX_LINES) flag = 1;
        }
        if (flag) printf("TOO HARD!\n");
        else printf("%d\n", best+lines);
    }
    return 0;
}

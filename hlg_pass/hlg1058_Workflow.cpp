/* Workflow */
#include <stdio.h>
#include <string.h>

#define MAXN 200
#define INF 99999

int vertex, edges, init_step, end_step_cnt;
bool is_end_step[MAXN], is_multiple[MAXN];
int map[MAXN][MAXN];
int min_time[MAXN];

int get_min_time(int cur)
{
    int i, ans, tmp;
    if (min_time[cur] != -1) return min_time[cur];
    if (is_multiple[cur])  ans = -1;
    else ans = INF;
    for (i = 0; i < vertex; i++) {
        if (map[i][cur]) {
            tmp = get_min_time(i);
            if (tmp == -1) continue;
            tmp++;
            if ((is_multiple[cur] && ans < tmp) || (!is_multiple[cur] && ans > tmp)) {
                ans = tmp;
            }
        }
    }
    if (ans != INF && ans != -1) min_time[cur] = ans;
    return min_time[cur];
}

int main()
{
    int n_case, i, a, b, ans, tmp;
    scanf("%d", &n_case);
    while (n_case--) {
        memset(map, 0, sizeof(map));
        memset(is_multiple, 0, sizeof(is_multiple));
        memset(is_end_step, 0, sizeof(is_end_step));

        scanf("%d %d", &vertex, &edges);
        scanf("%d %d", &init_step, &end_step_cnt);
        for (i = 0; i < end_step_cnt; i++) {
            scanf("%d", &a);
            is_end_step[a] = true;
        }
        for (i = 0; i < edges; i++) {
            scanf("%d %d", &a, &b);
            map[a][b] = 1;
        }
        for (i = 0; i < vertex; i++) {
            scanf("%d", &a);
            is_multiple[i] = a==1;
        }
        memset(min_time, -1, sizeof(min_time));
        min_time[init_step] = 1;
        ans = -1;
        for (i = 0; i < vertex; i++) {
            if (is_end_step[i]) {
                tmp = get_min_time(i);
                if (tmp != -1 && tmp != INF) {
                    if (ans == -1 || ans > tmp) ans = tmp;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

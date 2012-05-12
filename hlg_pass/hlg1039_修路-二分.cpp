// ÐÞÂ·
#include <stdio.h>
#include <string.h>

int seg[301];
int team[301];
int m, n;

int min(int a, int b){return a<b?a:b;}
int max(int a, int b){return a>b?a:b;}

int assign_work(int v)
{
    int i, j;
    memset(team, 0, sizeof(team));
    for (i = 0, j = 0; j < n && i < m; j++) {
        for (; team[j]+seg[i] <= v && i < m; i++) {
            team[j] += seg[i];
        }
    }
    return (i == m && j <= n);
}

int main()
{
    int tt, i, j, k, _min, _max, mid;
    scanf("%d", &tt);
    seg[0] = 0;
    while (tt--){
        scanf("%d %d", &m, &n); // seg m, team n
        _min = 99999;
        _max = 0;
        for (i = 0; i < m; i++) {
            scanf("%d", &seg[i]);
            _min = min(seg[i], _min);
            _max += seg[i];
        }
        while (_min < _max-1) {
            mid = _min + (_max - _min) / 2;
            if (assign_work(mid)) {
                _max = mid;
            }
            else {
                _min = mid;
            }
        }
        if (!assign_work(_min))
            assign_work(_max);
        _max = 0;
        for (i = 0; i < n; i++) {
            _max = max(team[i], _max);
        }
        printf("%d\n", _max);
    }
    return 0;
}

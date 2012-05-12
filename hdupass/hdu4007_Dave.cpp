/* Dave */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 1001

struct Point{
    int x, y;
};
Point p[MAXN], list[MAXN];

bool cmpx(const Point&a, const Point&b)
{
    return a.x < b.x;
}
bool cmpy(const Point&a, const Point&b)
{
    return a.y < b.y;
}

int main()
{
    int n, R, i, j, left, right, ans, cnt;

    while (~scanf("%d %d", &n, &R)) {
        for (i = 0; i < n; i++)  scanf("%d %d", &p[i].x, &p[i].y);
        sort(p, p+n, cmpx);
        right = 0;
        ans = 0;
        for (left = 0; left < n; left++) {
            for (; right < n; right++) {
                if (p[right].x - p[left].x > R) break;
            }
            for (i = left; i < right; i++) list[i-left] = p[i];
            cnt = right - left;
            sort(list, list+cnt, cmpy);
            j = 0;
            for (i = 0; i < cnt; i++) {
                for (; j < cnt; j++) {
                    if (list[j].y - list[i].y > R) break;
                }
                if (ans < j - i) ans = j - i;
            }
        }
        printf("%d\n", ans);
    }
}

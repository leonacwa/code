#include <stdio.h>
#define MAX (50000+1)

int stu[MAX];
int n, m, total;

int init_set(int n)
{
    int i;
    for (i = 0; i <= n; i++)
        stu[i] = i;
    total = n;
}
int find_set(int x)
{
    int pa = x;
    while (pa != stu[pa])
    {
        pa = stu[pa];
    }
    int t;
    while (x != pa)
    {
        t = stu[x];
        stu[x] = pa;
        x = t;
    }
    return pa;
}
int union_set(int a, int b)
{
    int fa, fb;
    fa = find_set(a);
    fb = find_set(b);
    if (fa == fb)
        return 0;
    total--;
    stu[fb] = fa;
    return 1;
}
int main()
{
    int a, b;
    int i, cnt;
    cnt = 0;
    scanf("%d %d\n", &n, &m);
    while (n != 0 && m != 0)
    {
        init_set(n);
        for (i = 0; i < m; i++)
        {
            scanf("%d %d\n", &a, &b);
            union_set(a, b);
        }
        printf("Case %d: %d\n", ++cnt, total);
        scanf("%d %d\n", &n, &m);
    }
    return 0;
}
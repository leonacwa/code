/*
    在http://acm.hdu.edu.cn上通过
*/
#include <stdio.h>
#include <string.h>

#define MAX (50000 + 256)
int h[MAX], s[MAX];
int t, n, a, b;

int lowbit(int x)
{
    return x & (-x);
}
int add(int i, int d, int n)
{
    h[i] += d;
    while (i <= n)
    {
        s[i] += d;
        i += lowbit(i);
    }
}
int sum(int i)
{
    int ss = 0;
    while (i >0)
    {
        ss += s[i];
        i -= lowbit(i);
    }
    return ss;
}
int main()
{
    int i, tt;
    char cmd[32];
    
    scanf("%d", &t);
    for (tt = 1; tt <= t; tt++)
    {
        printf("Case %d:\n", tt);
        scanf("%d", &n);
        memset(h, 0, sizeof(int)*MAX);
        memset(s, 0, sizeof(int)*MAX);
        
        for (i = 1; i <= n; i++)
        {
            scanf("%d", &h[i]);
            add(i, h[i], n);
        }
        scanf("%s", cmd);
        while (cmd[0] != 'E')
        {
            if (cmd[0] == 'A')
            {
                scanf("%d %d\n", &a, &b);
                add(a, b, n);
            }
            else if (cmd[0] == 'S')
            {
                scanf("%d %d\n", &a, &b);
                add(a, -b, n);
            }
            else if (cmd[0] == 'Q')
            {
                scanf("%d %d\n", &a, &b);
                printf("%d\n", sum(b) - sum(a-1));
            }
            scanf("%s", cmd);
        }
    }
    
}
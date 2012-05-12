/*
    z这回是用非递归的线段树做，参考 zkw 的。    
*/
#include <stdio.h>
#include <string.h>

#define MAXN (50000 + 5)
int T[4*MAXN]; //  特殊的线段树，第一个和最后一个位置不存放数据，因为是开区间，用于辨别[....]闭区间吧,maybe
int data[MAXN]; // 第一个位置不存数据，其实也可以存，下标减一即可。

int t, n, M;

void make_tree()
{
    memset(T, 0, sizeof(int)*4*MAXN);
    int i;
    for (i = M+M-1; i > 0; i--)
    {
        if (i >= M) // 下标是 M 时什么都不是，因为不存数据
        {
            T[i] = data[i - M];
        }
        else //if (i < M)
        {
            T[i] = T[i+i] + T[i+i+1];
        }
    }
}
void insert(int n, int val)  // 插入的是某个节点的值
{   /*
    n += M;
    T[n] += val;
    while (n > 1)
    {
        n >>=  1;
        T[n] = T[n + n ] + T[n + n +1];
    } */
    /*简版*/
    for (T[n+=M] += val, n >>= 1;n;n >>= 1)
        T[n] = T[n+n] + T[n+n+1];
}
int query(int s, int t) // 目的：正好找到左右两块区间
{
    /*
    int ss = 0;
    s += M - 1;
    t += M + 1;
    while (!((s^t)==1)) // 左右子树，左右开区间
    {
        if ( (s&1) == 0)
            ss += T[s + 1];
        if ( (t&1) == 1)
            ss += T[t - 1];
        s >>= 1; t >>= 1;
    }
    return ss;
    */
    /*简版*/
    int ss = 0;
    for (s+=M-1, t+=M+1;s^t^1;s>>=1, t>>=1)
    {
        if (s & 1) ss += T[s+1];
        if (t & 1) ss += T[t-1];
    }
    return ss;
}

int main()
{
    int i, tt, a, b;
    char cmd[32];
    
    scanf("%d", &t);
    for (tt = 1; tt <= t; tt++)
    {
        printf("Case %d:\n", tt);
        scanf("%d", &n);
        for (M = 1; M < (n+2); M <<= 1)
        ;
        for (i = 1; i <= n; i++)
            scanf("%d", &data[i]);
        
        make_tree();
        
        //for (i = 1; i <= n; i++) printf("%d  ",  query(i, i+1, 1)); printf("\n");
        scanf("%s", cmd);
        while (cmd[0] != 'E')
        {
            if (cmd[0] == 'A')
            {
                scanf("%d %d\n", &a, &b);
                insert(a, b);
                //for (i = 1; i <= n; i++) printf("%d  ",  query(i, i+1, 1)); printf("\n");
            }
            else if (cmd[0] == 'S')
            {
                scanf("%d %d\n", &a, &b);
                insert(a, -b);
                //for (i = 1; i <= n; i++) printf("%d  ",  query(i, i+1, 1)); printf("\n");
            }
            else if (cmd[0] == 'Q')
            {
                scanf("%d %d\n", &a, &b); //printf("Q [%d %d]", a, b);
                printf("%d\n", query(a, b));
            }
            scanf("%s", cmd);
        }
    }
    
}
/*
    线段树做的，第一次做，想吐血。
    
*/
#include <stdio.h>
#include <string.h>

#define MAXN (50000 + 5)
struct Node{
    int l, r, val;
};
struct Node T[3*MAXN];
int data[MAXN];

int t, n;

void make_tree(int ll, int rr, int num)
{   
    T[num].l = ll;
    T[num].r = rr;
    T[num].val = 0;
    if(ll+1 == rr)
    {
        T[num].val = data[T[num].l]; // T[num].l - > num - (num/2)*2 + 1
        return;
    }
    int mid = (ll+rr) >> 1;
    make_tree(ll, mid, num+num);
    make_tree(mid, rr, num+num+1);
    T[num].val = T[num+num].val + T[num+num+1].val;
    
    //printf("make_tree %d %d  %d   %d\n", ll, rr, T[num].val, num);
}
void insert(int ll, int rr, int val, int num)  // 插入的是某个节点的值
{   
    T[num].val += val;
    if (T[num].l == ll && T[num].r == rr)
        return;
    
    int mid = (T[num].l + T[num].r)>>1;
    if (rr <= mid)
        insert(ll, rr, val, num+num);
    else
        insert(ll, rr, val, num+num+1);
    
    //T[num].val = T[num+num].val + T[num+num+1].val;
}
int query(int ll, int rr, int num)  // 选择子节点的时候，逻辑判断出错了，Fuck. 查询区间的值
{
    if (ll == T[num].l && T[num].r == rr)
        return T[num].val;
    
    int t = 0;
    int mid = (T[num].l+T[num].r)>>1;
    if (rr <= mid)
        t += query(ll, rr, num+num);
    else if (mid <= ll)
        t += query(ll, rr, num+num+1);
    else
    {  //printf("in two");
        t = query(ll, mid, num+num);
        t += query(mid, rr, num+num+1);
    }
    return t;
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
        
        for (i = 1; i <= n; i++)
            scanf("%d", &data[i]);
        
        make_tree(1, n+1, 1);
        
        //for (i = 1; i <= n; i++) printf("%d  ",  query(i, i+1, 1)); printf("\n");
        scanf("%s", cmd);
        while (cmd[0] != 'E')
        {
            if (cmd[0] == 'A')
            {
                scanf("%d %d\n", &a, &b);
                insert(a, a+1, b, 1);  
                //for (i = 1; i <= n; i++) printf("%d  ",  query(i, i+1, 1)); printf("\n");
            }
            else if (cmd[0] == 'S')
            {
                scanf("%d %d\n", &a, &b);
                insert(a, a+1, -b, 1);
                //for (i = 1; i <= n; i++) printf("%d  ",  query(i, i+1, 1)); printf("\n");
            }
            else if (cmd[0] == 'Q')
            {
                scanf("%d %d\n", &a, &b); //printf("Q [%d %d]", a, b);
                printf("%d\n", query(a, b+1, 1));
            }
            scanf("%s", cmd);
        }
    }
    
}
/*
  poj2236
  并查集的使用，但是有条件，两台电脑必须是修好并且在距离范围内，每次修好一台电脑，都要尝试与其他修好的电脑联系，能联系的放入一个集合。
  询问时，先联系，后看他们是否在同一集合.
  必须记录任意两台电脑的距离，不要边维修边判断，修心超时。
  
*/
#include <stdio.h>
#include <string.h>

#define MAX  1003
struct Node{int x, y, r, f;};
struct Node node[MAX];
int n, d, dd;
int  map[MAX][MAX];
int R[MAX], rr;

 // 宏，只为了速度
#define DIS(x1, y1, x2, y2)  (((x2) - (x1))*((x2) - (x1)) + ((y2) - (y1))*((y2) - (y1)))

void make_set()
{
    int i, j;
    memset(node, 0, sizeof(struct Node)*MAX);
    for (i = 1; i <= n; i++)
    {
        scanf("%d %d",  &node[i].x, &node[i].y);
        node[i].r = 0;
        node[i].f = i;
    }
    memset(map, 0, sizeof(int)*MAX*MAX);
    for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
    if(DIS(node[i].x, node[i].y, node[j].x, node[j].y) <= dd)
    {
        map[i][j] = 1;
        map[j][i] = 1;
    }
}

int find_set(int x)
{
    int rx = x, t;
    while (node[x].f != x)
    {
        x = node[x].f;
    }
    while (rx != x)
    {
        t = node[rx].f;
        node[rx].f = x;
        rx = t;
    }
    return x;
}
int S(int p, int q)  // union_set
{
    int fp, fq;
    fp = find_set(p);
    fq = find_set(q);
    if (fp == fq)
        return fp;
    if (node[p].r && node[q].r 
        && map[p][q] == 1)
    {
        return node[q].f = fp;
    }
    return -1;
}
int main()
{
    int i, p, q, f;
    char op;
    
    scanf("%d %d", &n, &d);
    dd = d * d;
    make_set();
    rr = 0;
    while (EOF != scanf("\n%c", &op))
    {
        if (op == 'O')
        {
            scanf("%d", &p);
            if (node[p].r == 1)  // 重复修好的不用考虑
                continue;
            node[p].r = 1;
            R[rr++] = p;
            for (i = 0; i < rr - 1; i++)
            if (map[p][R[i]])
            {
                node[find_set(R[i])].f = p;
            }
        }
        else
        {
            scanf("%d %d", &p, &q);
            if(-1 != S(p, q))
            {
                printf("SUCCESS\n");
            }
            else
            {
                printf("FAIL\n");
            }
        }
    }
    return 0;
}
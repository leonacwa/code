/*
  poj2236
  ���鼯��ʹ�ã���������������̨���Ա������޺ò����ھ��뷶Χ�ڣ�ÿ���޺�һ̨���ԣ���Ҫ�����������޺õĵ�����ϵ������ϵ�ķ���һ�����ϡ�
  ѯ��ʱ������ϵ���������Ƿ���ͬһ����.
  �����¼������̨���Եľ��룬��Ҫ��ά�ޱ��жϣ����ĳ�ʱ��
  
*/
#include <stdio.h>
#include <string.h>

#define MAX  1003
struct Node{int x, y, r, f;};
struct Node node[MAX];
int n, d, dd;
int  map[MAX][MAX];
int R[MAX], rr;

 // �ֻ꣬Ϊ���ٶ�
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
            if (node[p].r == 1)  // �ظ��޺õĲ��ÿ���
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
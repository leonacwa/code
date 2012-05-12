// NOIP 2009 trade 3������ó��

/*
 ��1��n��·�����ҵ�һ���ط����룬��һ���ط�������ʹ�û������
 
 ������˼�����˱��˵Ľ��ⱨ�档
 
 SPFA�����ǲ��ǵ�����SPFA��
 ���Ѿ��Ǵﵽ������õĵز��ˣ�������Ŀ����εı��Ρ�
 ��׼ȷ��˵��Ӧ����ʹ����SPFA��һ��˼�룬���߽��и�������ֵ��
 
 ˼·��
��ĿҪ����Ǵ�1��n��·�����������·����һ������ĵ��һ�������ĵ㣬ʹ�û������
ÿ�����ˮ���۸�һ��������ÿ����һ���㣬��������������۸�ض��ǵ���������
·���ϵ�����˼۸�Ȼ���������������������ض���·���ϵ�������˼۸�ĵ�u��ȥ
�����۸�ĵ�v��ǰ����u����v��������u��v��ǰ�档

�㷨��
���е����������۸��ʼΪ�õ��ˮ���۸���������ֵΪ-1����ʾ�Ƿ���
��1��������max[1] = 0; û�л�����
��1������У��Ӷ���ͷ��ʼ���¸��㡣x = q[head];
���ڵ�ǰ���ڸ��µĵ�x��������x�����ĵ�y��������������������y�����������۸����������
�и��µĵ�y������У����ڶԺ���ĵ���и��£���û�п����ڸ��µĵ㣬�㷨��ɡ�

�ڽӱ�洢���Ż�����������ʱ�䡣

�������룬�������SPFA����Ȼ���˵��㷨����д��SPFA�������Ҳ����װ���
��������������SPFA�㷨�Ŀ�ܣ��ѵ�ָ�������?
���⡣

*/
#include <stdio.h>
#include <string.h>

const int  M = 500000+8;
const int  N = 100000+8;
const int  QN = 100000+8;

struct E{
    int v;
    E* next;
};
E e[M*2];
int ei;
E* u[N];

int price[N];
int cur[N], max[N]; // ��ѹ���۸��������
int q[QN], head, tail;
bool set[N];
int n, m, ans;

int spfa()
{
    int x, y, t;
    
    // ��ֵΪ����,��ʾ��ʼ��Ļ����ȵ�1�Ļ���0С������˵�ǡ��޷������������Ƿ�������
    memset(max, -1, sizeof(max)); 
    memset(set, 0, sizeof(set));
    
    head = 0; 
    tail = 1;
    q[0] = 1;
    set[1] = true;
    max[1] = 0; //��ʼ��ӯ��Ϊ0
    
    for (int i = 1; i <= n; i++)
        cur[i] = price[i];
    
    while (head != tail){
        x = q[head];
        head = (head+1)%QN;
        set[x] = false;
        
        for (E* pe = u[x]; pe; pe = pe->next){ // ���ձ߽��и���
            y = pe->v;
            if (cur[y] > cur[x] || max[y] < max[x]){
                
                if (cur[y] > cur[x]) // ���¹���۸�
                    cur[y] = cur[x];
                
                if (max[y] < max[x]) // ���»���
                    max[y] = max[x];
                
                if ((t=price[y] - cur[y]) > max[y]) // ���»���
                    max[y] = t;
                
                if (!set[y]){ // ���¹��ĵ�������
                    q[tail] = y;
                    set[y] = true;
                    tail = (tail+1)%QN;
                }
            }
            
        }
        
    }
    
    return max[n];
}
int main()
{
    freopen("trade.in", "r", stdin);
    freopen("trade.out", "w", stdout);
    
    memset(u, 0, sizeof(u));
    
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++)
        scanf("%d", &price[i]);
    
    ei = 0;
    for (int i = 1, x, y, z; i <= m; i++){
        scanf("%d %d %d", &x, &y, &z);
        //  (x->y)
        e[ei].v = y;
        e[ei].next = u[x];
        u[x] = &e[ei];
        ++ei;
        // (y->x)
        if (2 == z){
            e[ei].v = x;
            e[ei].next = u[y];
            u[y] = &e[ei];
            ++ei;
        }
    }
    
    ans = 0;
    
    ans = spfa();
        
    if (ans > 0) {
        printf("%d\n", ans);
    }
    else {
        printf("0\n");
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}

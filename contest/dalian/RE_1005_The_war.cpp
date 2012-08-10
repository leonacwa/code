#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define MM 200005// �����ֵ
#define NN 10005 // �����ֵ
int F, R;
int idx; // ����
int bCnt;// ��ͨ��֧������ branch cnt
int tim;// ��¼ʱ���

int low[NN]; // Low(u)Ϊu��u����������ͨ���Ǹ��ӱ�׷�ݵ�������Ľڵ㣬��DFS�����С�Ľڵ�
int dfn[NN]; // ������ȱ��
int bel[NN]; // bel[u] = k���ڵ�u���ڷ�֧k
int deg[NN]; // ��¼ÿ����֧�Ķ�

typedef struct node{
   int v;
   int vis;
   int e;
   struct node *nxt, *op;        
}NODE;

NODE edg[MM];
NODE *link[NN];
NODE *par[NN]; // ��¼���ﶥ��v������

int Min(int a, int b){
    return a < b ? a : b;
}

void Add(int u, int v, int e){ // �ӱ�
     idx++;
     edg[idx].v = v;
     edg[idx].vis = 0;
     edg[idx].nxt = link[u];
     edg[idx].e = e;
	 link[u] = edg + idx;
	 edg[idx].op = edg + idx + 1; // ��ʾ�����
	 idx++;
     edg[idx].v = u;
     edg[idx].vis = 0;
     edg[idx].nxt = link[v];
     edg[idx].e = e;
	 link[v] = edg + idx;
     edg[idx].op = edg + idx - 1;
}

void dfs(int u){// ��������������Tarjan��ǿ��ͨ��֧
     int v;
     dfn[u] = low[u] = ++tim;
     for (NODE *p = link[u]; p; p = p->nxt){
         if (p->vis) continue;
         p->vis = p->op->vis = 1; // ���ڼӵ���˫��ߣ���������߷��ʺ󣬷����ҲҪ���
         v = p->v;
         if (!dfn[v]){
            par[v] = p->op; // ����dfs�����ǽ�һ��������������ÿ�����ǰ������Ψһ��
            dfs(v);
            low[u] = Min(low[u], low[v]);
         }else{
            low[u] = Min(low[u], dfn[v]);
         }
     }
}

void Part(int u){// ��ÿ���������ڷ�֧
     bel[u] = bCnt;
     for (NODE *p = link[u]; p; p = p->nxt){
         if (p->vis && !bel[p->v]){
            Part(p->v);
         }
     }
}
int ans, cnt;
void Solve(){
     int i, u, v, x, y, leaf;
     tim = 0;
     dfs(1);
     for (v = 2; v <= F; v++){// ɾ����
         u = (par[v])->v;
         if (dfn[u] < low[v]){// �ű�<u, v>������
         	//printf("%d %d %d\n", u, v, par[v]->e);
         	ans = max(ans, par[v]->e);
         	cnt++;
            (par[v])->vis = (par[v])->op->vis = 0; 
         }
     }
     /*
     bCnt = 0;
     for (u = 1; u <= F; u++){
         if (!bel[u]){
            bCnt++;
            Part(u);
         }
     }
     memset(deg, 0, sizeof(deg));
     for (u = 1; u <= F; u++){ // �ҵ�ÿ����֧�Ķȣ������������ڲ�ͬ��֧�ڵ��bel����һ��
         for (NODE *p = link[u]; p; p = p->nxt){
             x = bel[u]; y = bel[p->v];
             if (x != y){
                deg[x]++;
             }
         }
     }
     
     leaf = 0;
     for (i = 1; i <= bCnt; i++){// ��¼��Ϊ1�ķ�֧
         if (deg[i] == 1) leaf++;
     }
     
     if (leaf == 1){
        puts("0");
     }else {
           printf("%d\n", (leaf + 1) / 2);
     }
     */
}

int main()
{
    int a, b, c;
    while (scanf("%d%d", &F, &R) != EOF) {
	    memset(link, 0, sizeof(link));
		idx = 0;
	    while(R--){
	       scanf("%d%d%d", &a, &b, &c);
	       Add(a, b, c);
	    }
	    ans = -1;
	    cnt = 0;
	    Solve();
	    if (cnt <= 2) {
			ans = -1;
		}
	    printf("%d\n", ans);
	}
    return 0;
}

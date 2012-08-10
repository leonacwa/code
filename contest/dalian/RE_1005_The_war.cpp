#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
#define MM 200005// 边最大值
#define NN 10005 // 点最大值
int F, R;
int idx; // 边数
int bCnt;// 连通分支个个数 branch cnt
int tim;// 记录时间戳

int low[NN]; // Low(u)为u或u的子树中能通过非父子边追溯到的最早的节点，即DFS序号最小的节点
int dfn[NN]; // 深度优先标号
int bel[NN]; // bel[u] = k，节点u属于分支k
int deg[NN]; // 记录每个分支的度

typedef struct node{
   int v;
   int vis;
   int e;
   struct node *nxt, *op;        
}NODE;

NODE edg[MM];
NODE *link[NN];
NODE *par[NN]; // 记录到达顶点v的树边

int Min(int a, int b){
    return a < b ? a : b;
}

void Add(int u, int v, int e){ // 加边
     idx++;
     edg[idx].v = v;
     edg[idx].vis = 0;
     edg[idx].nxt = link[u];
     edg[idx].e = e;
	 link[u] = edg + idx;
	 edg[idx].op = edg + idx + 1; // 表示反向边
	 idx++;
     edg[idx].v = u;
     edg[idx].vis = 0;
     edg[idx].nxt = link[v];
     edg[idx].e = e;
	 link[v] = edg + idx;
     edg[idx].op = edg + idx - 1;
}

void dfs(int u){// 建深搜树，类似Tarjan求强连通分支
     int v;
     dfn[u] = low[u] = ++tim;
     for (NODE *p = link[u]; p; p = p->nxt){
         if (p->vis) continue;
         p->vis = p->op->vis = 1; // 由于加的是双向边，所以正向边访问后，反向边也要标记
         v = p->v;
         if (!dfn[v]){
            par[v] = p->op; // 由于dfs作用是建一棵深搜树，所以每个点的前边是是唯一的
            dfs(v);
            low[u] = Min(low[u], low[v]);
         }else{
            low[u] = Min(low[u], dfn[v]);
         }
     }
}

void Part(int u){// 将每个点归入对于分支
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
     for (v = 2; v <= F; v++){// 删除桥
         u = (par[v])->v;
         if (dfn[u] < low[v]){// 桥边<u, v>的条件
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
     for (u = 1; u <= F; u++){ // 找到每个分支的度，任意两个属于不同分支节点的bel都不一样
         for (NODE *p = link[u]; p; p = p->nxt){
             x = bel[u]; y = bel[p->v];
             if (x != y){
                deg[x]++;
             }
         }
     }
     
     leaf = 0;
     for (i = 1; i <= bCnt; i++){// 记录度为1的分支
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

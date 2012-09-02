#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#define ll long long
#define PI acos(-1.0)
#define eps 1e-9
#define MOD 1000000007
#define INF 1000000000
using namespace std;

template<class T> T f_min(T x,T y){return x<y?x:y;}
template<class T> T f_max(T x,T y){return x>y?x:y;}
template<class T> T f_abs(T x){return x<0?-x:x;}

int M;
char mp[20][20];
int fa[20];
ll blk[20];
vector<int>vec[20];

int findf(int x){
	if(x!=fa[x])fa[x]=findf(fa[x]);
	return fa[x];
}

void get_data(){
	int i,j;
	scanf("%d",&M);
	M <<= 1;
	for(i=0;i<M;i++) scanf("%s",mp[i]);
	for(i=0;i<M;i++) fa[i]=i,vec[i].clear(); // 初始化
	for(i=0;i<M;i++) { // 看那些人是必须在一块的
		for(j=0;j<M;j++){
			if(i==j||mp[i][j]=='N')continue;
			int a,b;
			a=findf(i);
			b=findf(j);
			if(a!=b){
				fa[a]=b;
			}
		}
	}
	
	for(i=0;i<M;i++){ // 每一块都有那些人
		fa[i]=findf(i);
		vec[fa[i]].push_back(i);
	}
}

bool mk[20];
int ord[20],whr[20];
bool ok(int vi){
	int i,j,a,b;
	for(i=0;i<vec[vi].size();i++){
		for(j=i+1;j<vec[vi].size();j++){
			a=ord[i];
			b=ord[j];
			if(mp[b][a]=='Y')return 0;
			
		}
	}
	return 1;
}

void dfs(int loc,int vi){
	if(loc==vec[vi].size()){
		if(ok(vi))blk[vi]++;
		return;
	}
	int i;
	for(i=0;i<vec[vi].size();i++){
		if(mk[i])continue;
		mk[i]=1;
		ord[loc]=vec[vi][i];
		dfs(loc+1,vi);
		mk[i]=0;
	}
}
void cal_blk(){ // 深搜计算每块的人能组成的排列数量
	int i;
	for(i=0;i<M;i++){
		if (vec[i].empty())continue;
		memset(mk,0,sizeof mk);
		blk[i]=0;
		dfs(0,i);
	}
}
ll res;
int am[20],pm[20];
ll C[20][20];
void get_C(){
	int i,j;
	for(i=0;i<20;i++){
		C[i][0]=C[i][i]=1;
		for(j=1;j<i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	
	}
}
ll cal(int x[],int n){
	ll r=1;
	int i,now=0,a;
	for(i=0;i<n;i++){
		a=x[i];
		r=r*C[now+vec[a].size()][vec[a].size()]*blk[a];
		now+=vec[a].size();
	}
	return r;
}
void dfs2(int loc,int as,int ps,int an,int pn){
	if(as>M/2||ps>M/2)return;
	if(loc==M){
	//	printf("%lld %lld \n",cal(am,an),cal(pm,pn));
		res+=cal(am,an)*cal(pm,pn);
		return;
	}
	if(fa[loc]==loc){
		am[an]=loc;
		dfs2(loc+1,as+vec[loc].size(),ps,an+1,pn);
		pm[pn]=loc;
		dfs2(loc+1,as,ps+vec[loc].size(),an,pn+1);	
	}else dfs2(loc+1,as,ps,an,pn);
}
void run(){
	int i;
	for(i=0;i<M;i++) { // 不可能存在的解
		if(vec[i].size()>M/2){
			printf("0\n");
			return;
		}
	}
	cal_blk(); // 计算每个块的拓扑排序数
	res=0;
	dfs2(0,0,0,0,0);
	printf("%lld\n",res);
}
/*
8
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNN

31
3
NYYNNN
NNNNNN
NNNNNN
NNNNNN
NNNNNN
NNNNNN
*/
int main(){
	get_C();
	int t,i=0;
	scanf("%d",&t);
	while(t--){
		get_data();
		run();
	}
	return 0;
}

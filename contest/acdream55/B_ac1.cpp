#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <queue>
using namespace std;

typedef long long LL;

const int maxn = 131080;

int bit[20];
int maxd;
char c[20][20];
LL dp[maxn];
int val[maxn];

int getbit(int vv) // 获得vv有多少位
{
	int ret = 0;
	while(vv){
		if(vv&1) ret += 1;
		vv >>= 1;
	}
	return ret;
}

int main()
{
#if 0
	freopen ("test.txt", "rt", stdin);
#endif
	LL ret;
	int i,j,n,all,mid,tmp;
	int t;
	bit[0] = 1;
	for(i = 1;i < 20;i ++)
		bit[i] = bit[i-1]*2;

	scanf("%d",&t);
	while(t --)
	{
		scanf("%d",&n);
		all = n*2;
		for(i = 0;i < all;i ++){
			scanf("%s",c[i]);
			val[i] = 0;
			for(j = 0;j < all;j ++){
				if(c[i][j] == 'Y') {
					val[i] += bit[j]; // val[i]表示i需要那些人先进行
				}
			}
			//printf("%d %d\n",i,val[i]);
		}

		memset(dp,0,sizeof(dp));
		maxd = (1<<all)-1;
		dp[0] = 1;

		for(i = 0;i <= maxd;i ++) // 最多2^16
		{
			tmp = getbit(i); // i 状态有多少人
			if(tmp > n) continue; // 一个时间段不能有超过n人
			//printf("%d %d\n",i,tmp);
			for(j = 0;j < all;j ++) { // i 状态加上第j个人后的状态有多少种排列方式
				if(bit[j]&i) continue;
				if((i&val[j]) == val[j]) { // i 状态满足j人的依赖
					//printf("%d %d %lld %lld\n",i,i+bit[j],dp[i],dp[i+bit[j]]);
					dp[i+bit[j]] += dp[i];
					//	printf("%d %d %lld %lld\n",i,i+bit[j],dp[i],dp[i+bit[j]]);
				}
			}
		}
		ret = 0;
		//printf("%d %d\n",n,maxd);
		for(i = 0;i <= maxd;i ++) {
			tmp = getbit(i);
			//printf("%d %d\n",i,tmp);
			if(tmp != n) continue; // 安排一个时间段只能有n人
			//printf("%d %d %lld %lld\n",i,maxd-i,dp[i],dp[maxd-i]);
			if(dp[i] == 0 || dp[maxd-i] == 0) continue;
			ret = ret + dp[i] * dp[maxd-i];
		}
		printf("%lld\n",ret);
	}
	return 0;
}

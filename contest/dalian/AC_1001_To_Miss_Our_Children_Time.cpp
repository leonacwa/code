#include <cstdio>
#include <algorithm>
using namespace std;
struct vNode {
	int l, w, h, type;
}v[1005];
long long dp[1005],ans;
bool cmp(const vNode &a,const vNode &b)
{
	if(a.l != b.l)	return a.l < b.l;
	if(a.w != b.w)	return a.w < b.w;
	return a.type > b.type;
}
int main()
{
	int n,i,j,temp;
	while(scanf("%d",&n), n) {
		ans = 0;
		for(i = 0; i < n; i++) {
			scanf("%d%d%d%d",&v[i].l,&v[i].w,&v[i].h,&v[i].type);
			if(v[i].l<v[i].w) {
				temp=v[i].l;
				v[i].l=v[i].w;
				v[i].w=temp;
			}
		}
		sort(v,v+n,cmp);
		for(i=0;i<n;i++) {
			dp[i]=v[i].h;
			for(j=0;j<i;j++) {
				if(v[i].type==0) {
					if(v[i].l>=v[j].l&&v[i].w>=v[j].w)
						dp[i]=max(dp[i],dp[j]+v[i].h);
				} else if(v[i].type==1) {
					if(v[i].l>=v[j].l&&v[i].w>=v[j].w&&(v[i].l>v[j].l||v[i].w>v[j].w))
						dp[i]=max(dp[i],dp[j]+v[i].h);
				} else {
					if(v[i].l > v[j].l && v[i].w > v[j].w)
						dp[i] = max(dp[i], dp[j] + v[i].h);
				}
			}
			ans=max(ans,dp[i]);
		}
		printf("%I64d\n",ans);
	}
	return 0;
}

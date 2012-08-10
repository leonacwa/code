#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;
const int MAX = 1010;
struct point{ int x,y;};
point p[MAX];
int gcd(int n,int m)
{
	return m == 0 ? n : gcd(m,n%m);
}
int intp_insegment(point a, point b)
{
	int aa = abs(b.y - a.y), bb = abs(b.x - a.x);
	if(aa == 0 && bb == 0)	return 0;
	if(aa == 0)	return bb - 1;
	if(bb == 0)	return aa - 1;
	return gcd(aa, bb) - 1;
}
long long intp_edge(point p[],int n)
{
	long long ans = n // 已经等于n了
	for(int i=0; i<n; i++)
		ans += intp_insegment(p[i], p[(i+1)%n]);
	return ans;
}
double area_polygon(point p[],int n)
{
	double s = 0.0;
	for(int i=0; i<n; i++)
		s += p[(i+1)%n].y *1ll* p[i].x - p[(i+1)%n].x*1ll * p[i].y;
	return fabs(s)/2.0;
} 
long long intp_inpolygon(point p[],int n)
{
	double area = area_polygon(p,n);
	long long pinedge = intp_edge(p,n);
	return (long long)(area) - pinedge/2ll + 1;
}
int main()
{
	int n, runs;
	scanf("%d",&runs);
	while(runs--) {
		scanf("%d",&n);
		point tp;
		tp.x = 0, tp.y = 0;
		for(int i=0; i<n; i++) {
			int x, y;
			scanf("%d %d",&x,&y);
			p[i].x = x + tp.x, p[i].y = y + tp.y;
			tp = p[i];
		}

		long long ans = intp_inpolygon(p,n);
		printf("%lld\n",ans);
	}
	return 0;
}


/* K  wolf5x */
#include<stdio.h>
#include<string.h>
#define CLEAR(a) memset(a,0,sizeof(a));
const int N=2200;
double p[N][4];//1 left 2 right
double e[N][4];
inline double max(double x1,double x2) {
	return x1+x2;
	return x1>x2?x1:x2;
}
int main() {
	int t;
	scanf("%d",&t);
	while (t--) {
		CLEAR(p);
		int n,a,b;
		scanf("%d%d%d",&n,&a,&b);
		int i,j;
		for (i=1;i<=n;i++) {
			scanf("%lf%lf%lf%lf",&p[i][0],&p[i][1],&p[i][2],&p[i][3]);
		}
		double current[4];
		for (i=n;i>=0;i--) {
			e[i][1]=0;
			e[i][2]=0;
			e[i][3]=0;
			current[1]=1;
			current[2]=1;
			current[3]=1;
			for (j=i+a;j<=i+b;j++) {
				if (j>n) {
					e[i][1]+=current[1];
					e[i][2]+=current[2];
					e[i][3]+=current[3];
					break;
				}
				else {
					e[i][1]+=current[1]*(p[j][2]*(1+e[j][2])+p[j][3]*(1+e[j][3]));
					e[i][2]+=current[2]*(p[j][1]*(1+e[j][1])+p[j][3]*(1+e[j][3]));
					e[i][3]+=current[3]*(p[j][1]*(1+e[j][1])+p[j][2]*(1+e[j][2])+p[j][3]*(1+e[j][3]));
					current[1]*=p[j][0]+p[j][1];
					current[2]*=p[j][0]+p[j][2];
					current[3]*=p[j][0];
				}
			}
		}
		printf("%.16f\n",e[0][3]);
	}
	return 0;
}

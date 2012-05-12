/**********************************************************************
*        Bitonic path (详见《算法导论》 P217)                                                                                   
*        一个人从p1严格地增的走到pn，然后再严格递减的回到p1;求总路径的最小值；                      
*        对于1 <= i <= j <= n, 我们定义P(i, j)是一条包含了P1, P2, P3 …… Pj的途径;                   
*        这条路径可以分成2部分：递减序列与递增序列                                                                
*        起点是Pi(1 <= i <= j)，拐点是P1，终点是Pj, P[i, j]为其最小值；                                     
*        状态转移方程为： 
*        b[1,2]=|P1P2|,
*        i < j-1时， b[i,j] = b[i,j-1] + |Pj-1Pj|    点Pj-1在递增序列中，                                                
*        i = j-1时， b[i,j] = min{ b[k,j-1] + |PkPj|, 1<= k < j-1 }  点Pj-1在递减序列中                       
*        b[n,n] = b[n-1,n] +|Pn-1Pn|
**********************************************************************/
#include <cstdio>
#include <cmath>
#include <climits>
#include <cfloat>
#include <iostream>
using namespace std;

const int NN = 2000 + 10;
struct Point {
	int x, y;
};

int n;
Point pl[NN];
double dis[NN][NN];
double f[NN][NN];

double getDis(Point a, Point b)
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x*x + y*y); 
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &pl[i].x, &pl[i].y);
			for (int j = 0; j <= i; ++j) {
				dis[i][j] = dis[j][i] = getDis(pl[i], pl[j]);
			}
		}
		for (int i = 0; i < n; ++i) {
			f[i][0] = dis[i][0];
		}
		for (int i = 1; i < n; ++i) {
			f[i+1][i] = DBL_MAX;
			for (int j = 0; j < i; ++j) {
				f[i+1][j] = f[i][j] + dis[i][i+1];
				f[i+1][i] = min(f[i+1][i], f[i][j] + dis[j][i+1]);
			}
		}
		f[n-1][n-1] = f[n-1][n-2] + dis[n-1][n-2];
		printf("%.2f\n", f[n-1][n-1]);
	}
	return 0;
}


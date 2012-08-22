/**********************************************************************
*        Bitonic path (������㷨���ۡ� P217)                                                                                   
*        һ���˴�p1�ϸ�������ߵ�pn��Ȼ�����ϸ�ݼ��Ļص�p1;����·������Сֵ��                      
*        ����1 <= i <= j <= n, ���Ƕ���P(i, j)��һ��������P1, P2, P3 ���� Pj��;��;                   
*        ����·�����Էֳ�2���֣��ݼ��������������                                                                
*        �����Pi(1 <= i <= j)���յ���P1���յ���Pj, P[i, j]Ϊ����Сֵ��                                     
*        ״̬ת�Ʒ���Ϊ�� 
*        b[1,2]=|P1P2|,
*        i < j-1ʱ�� b[i,j] = b[i,j-1] + |Pj-1Pj|    ��Pj-1�ڵ��������У�                                                
*        i = j-1ʱ�� b[i,j] = min{ b[k,j-1] + |PkPj|, 1<= k < j-1 }  ��Pj-1�ڵݼ�������                       
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


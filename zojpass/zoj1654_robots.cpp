/* zoj 1654 Plae the Robots
 * 转换成二分图，求最大匹配
 * */
#include <cstdio>
#include <cstring>


/* 二分图最大匹配(hungary邻接阵形式)
 * 二分图最大匹配,hungary算法,邻接阵形式,时间复杂度O(m*m*n)
 * 传入二分图大小m,n和邻接阵mat,非零元素表示有边
 * 返回最大匹配数
 * m1,m2返回一个最大匹配,未匹配顶点match值为-1
 * */
const int MAXN = 50*50;

int m1[MAXN], m2[MAXN];
int mat[MAXN][MAXN];
// hungary 算法
int maxmatch(int n1, int n2, int mat[][MAXN], int m1[], int m2[]) { // BFS找增广路
	int p, q, s[MAXN], t[MAXN], ret = 0, i, j, k;
	memset(m1, -1, sizeof(m1[0])*n1);
	memset(m2, -1, sizeof(m2[0])*n2);
	for (i = 0; i < n1; ++i) {
		memset(t, -1, sizeof(t[0])*n2);
		for (s[p=q=0] = i; p <= q && m1[i] < 0 ; ++p) {
			for (k = s[p], j = 0; j < n2 && m1[i] < 0; ++j) {
				if (mat[k][j] && t[j] < 0) {
					s[++q] = m2[j], t[j] = k;
					if (s[q] < 0) {
						for (p = j; p >= 0; j = p) {
							m2[j] = k = t[j];
							p = m1[k];
							m1[k] = j;
						}
					}
				}
			}
		}
		if (m1[i] >= 0) ++ret;
	}
	return ret;
}

char ms[55][55];
int xn[55][55], yn[55][55];

int main()
{
	int run, runs;
	scanf("%d", &runs);
	for (run = 1; run <= runs; ++run) {
		memset(xn, -1, sizeof(xn));
		memset(yn, -1, sizeof(yn));
		int m, n, n1, n2;
		scanf("%d%d", &m, &n);
		for (int i = 0; i < m; ++i) scanf("%s", ms[i]);
		int num = -1;
		for (int i = 0; i < m; ++i) {
			bool flag = true;
			for (int j = 0; j < n; ++j) {
				if (ms[i][j] == 'o') {
					if (flag) num++;
					xn[i][j] = num;
					flag = false;
				} else if (ms[i][j] == '#') {
					flag = true;
				}
			}
		}
		n1 = num + 1;
		num = -1;
		for (int j = 0; j < n; ++j) {
			bool flag = true;
			for (int i = 0; i < m; ++i) {
				if (ms[i][j] == 'o') {
					if (flag) num++;
					yn[i][j] = num;
					flag = false;
				} else if (ms[i][j] == '#') {
					flag = true;
				}
			}
		}
		n2 = num + 1;
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (xn[i][j] != -1) {
					mat[xn[i][j]][yn[i][j]] = 1;
				}
			}
		}
		printf("Case :%d\n%d\n", run, maxmatch(n1, n2, mat, m1, m2));
	}
	return 0;
}

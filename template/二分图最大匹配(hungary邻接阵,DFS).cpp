/* 二分图最大匹配(hungary邻接阵形式)
 * :顶分为X和Y两个部分，返回的结果是X和Y的最大匹配
 * 二分图最大匹配,hungary算法,邻接阵形式,时间复杂度O(m*m*n)
 * 传入二分图大小m,n和邻接阵mat,非零元素表示有边
 * 返回最大匹配数
 * m1,m2返回一个最大匹配,未匹配顶点match值为-1
 * DFS形式比非DFS形式慢一些，但那时代码短些
 * */

#include <cstdio>
#include <cstring>

const int MAXN = 305;

int n1, n2;
int m1[MAXN], m2[MAXN];
int mat[MAXN][MAXN];
bool mk[MAXN];

bool dfs(int u) {
	for (int i = 0; i < n2; ++i) {
		if (mat[u][i] && !mk[i]) {
			mk[i] = true;
			if (m2[i] == -1 || dfs(m2[i])) {
				m2[i] = u;
				m1[u] = i;
				return true;
			}
		}
	}
	return false;
}

int maxmatch() {
	int ret = 0;
	memset(m1, -1, sizeof(m1[0])*n1);
	memset(m2, -1, sizeof(m2[0])*n2);
	for (int i = 0; i < n1; ++i) {
		if (m1[i] == -1) {
			memset(mk, 0, sizeof(mk[0]) * n2);
			if (dfs(i)) ++ret;
		}
	}
	return ret;
}


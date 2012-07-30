/* 二分图最大匹配(hungary邻接阵形式)
 * :顶分为X和Y两个部分，返回的结果是X和Y的最大匹配
 * 二分图最大匹配,hungary算法,邻接阵形式,时间复杂度O(m*m*n)
 * 传入二分图大小m,n和邻接阵mat,非零元素表示有边
 * 返回最大匹配数
 * m1,m2返回一个最大匹配,未匹配顶点match值为-1
 * */
const int MAXN = 505;

int m1[MAXN], m2[MAXN];
int mat[MAXN][MAXN];
/* hungary 算法 */
int maxmatch(int n1, int n2, int mat[][MAXN], int m1[], int m2[]) { /* BFS找增广路 */
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


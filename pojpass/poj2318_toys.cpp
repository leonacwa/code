/* 从最左边的0号挡板(边界)开始，输出每块挡板的右边到第二块挡板左边之间有多少点。
 * 善法：叉积 + 二分查找。
 * 二分查找要点：对于一个挡板i，如果点在i的左边，则向左走，如果在i的右边，向右走，直到在i到i+1挡板之间
 * */
#include <stdio.h>
#include <string.h>

const int NN = 5000 + 5;

int x, y, x1, y1, x2, y2, n, m, U[NN], L[NN];
int box[NN];

int xmult(int x0, int y0, int x1, int y1, int x2, int y2)
{
	return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
}

int find(int x, int y)
{
	int l = 0, r = n+1, m;
	while (l < r - 1) {
		m = (r - l) / 2 + l;
		if (xmult(L[m], y2, x, y, U[m], y1) < 0) {
			r = m;
		} else {
			l = m;
		}
	}
	return l;
}

int main()
{
	while (EOF != scanf("%d %d %d %d %d %d", &n, &m, &x1, &y1, &x2, &y2) && n > 0) {
		U[0] = 	L[0] = x1;
		U[n+1] = L[n+1] = x2;
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d", &U[i], &L[i]);
		}
		memset(box, 0, sizeof(box));
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &x, &y);
			int pos = find(x, y);
			box[pos]++;
		}
		for (int i = 0; i <= n; ++i) {
			printf("%d: %d\n", i, box[i]);
		}
		printf("\n");
	}
	return 0;
}


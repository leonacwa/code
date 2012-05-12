/* 用二维矩阵表示正六边形，从一个正六边形访问相邻正六边形方法
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int Row = 15, Col = 15, NN = 15;
const int sx = 7, sy = 7;
const int dx[6] = {-1, 0, 1, 1, 0, -1}, dy[6] = {-1, -1, 0, 1, 1, 0};
int n;
int f[NN][Row][Col];

int main()
{
	memset(f, 0, sizeof(f));
	f[0][sx][sy] = 1;
	for (int k = 1; k <= 15; ++k) {
		for (int x = 0; x < Row; ++x) {
			for (int y = 0; y < Col; ++y) {
				for (int i = 0; i < 6; ++i) {
					int x2 = x + dx[i], y2 = y + dy[i];
					if (0 <= x2 && x2 < Row && 0 <= y2 && y2 < Col) {
						f[k][x][y] += f[k-1][x2][y2];
					}
				}
			}
		}
	}
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d", &n);
		printf("%d\n", f[n][sx][sy]);
	}
	return 0;
}


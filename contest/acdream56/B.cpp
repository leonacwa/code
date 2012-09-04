/*  Save the Students!
 *  http://livearchive.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3995
 *  */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_M = 205, offset = 100;
bool mat[MAX_M][MAX_M];

int cross(int x1, int y1, int x2, int y2, int x, int y) {
	int ax = x1 - x, ay = y1 - y, bx = x2 - x, by = y2 - y;
	return ax * by - ay * bx;
}

bool inTri(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
	return abs(cross(x1, y1, x2, y2, x3, y3)) == 
		abs(cross(x1, y1, x2, y2, x, y)) +
		abs(cross(x1, y1, x3, y3, x, y)) +
		abs(cross(x3, y3, x2, y2, x, y));
}

bool inCir(int x0, int y0, int x, int y, int r) {
	return (x-x0)*(x-x0) + (y-y0)*(y-y0) <= r*r;
}

void Tri() {
	int x1, y1, x2, y2, x3, y3;
	scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
	x1 += offset, y1 += offset, x2 += offset, y2 += offset, x3 += offset, y3 += offset;
	for (int i = 0; i < MAX_M; ++i) {
		for (int j = 0; j < MAX_M; ++j) {
			if (!mat[i][j] && inTri(i, j, x1, y1, x2, y2, x3, y3)) {
				mat[i][j] = true;
			}
		}
	}
}

void Cir() {
	int x, y, r;
	scanf("%d%d%d", &x, &y, &r);
	x += offset, y += offset;
	for (int i = 0; i < MAX_M; ++i) {
		for (int j = 0; j < MAX_M; ++j) {
			if (!mat[i][j] && inCir(i, j, x, y, r)) {
				mat[i][j] = true;
			}
		}
	}
}

void Squ() {
	int x, y, l;
	scanf("%d%d%d", &x, &y, &l);
	x += offset, y += offset;
	for (int i = 0; i < MAX_M; ++i) {
		for (int j = 0; j < MAX_M; ++j) {
			if (!mat[i][j] && x <= i && i <= x+l && y <= j && j <= y+l) {
				mat[i][j] = true;
			}
		}
	}
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		memset(mat, 0, sizeof(mat));
		int n;
		char cmd[32];
		scanf("%d", &n);
		while (n--) {
			scanf("%s", cmd);
			if (cmd[0] == 'T') Tri();
			else if (cmd[0] == 'C') Cir();
			else if (cmd[0] == 'S') Squ();
			else for(;;) puts("");;
		}
		int ans = 0;
		for (int i = 0; i < MAX_M; ++i) {
			for (int j = 0; j < MAX_M; ++j) {
				if (mat[i][j]) ++ans;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

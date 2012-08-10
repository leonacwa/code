#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0}, dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

struct Node {
	int x, y;
	Node(int tx = 0, int ty = 0) : x(tx), y(ty)
	{}
};

int mat[10][10];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		char s[10], t[10];
		scanf("%s", s);
		scanf("%s", t);
		//printf("%s\n%s\n", s, t);
		int sx = s[0] - 'a', sy = s[1] - '1', ex = t[0] - 'a', ey = t[1] - '1';
		queue<Node> Q;
		memset(mat, -1, sizeof(mat));
		mat[sx][sy] = 0;
		Q.push(Node(sx, sy));
		while (false == Q.empty()) {
			Node tn = Q.front();
			Q.pop();
			for (int i = 0; i < 8; ++i) {
				int x = tn.x + dx[i], y = tn.y + dy[i];
				if (0 <= x && x < 8 && 0 <= y && y < 8 && (mat[x][y] == -1)) {
					mat[x][y] = mat[tn.x][tn.y] + 1;
					Q.push(Node(x, y));
					if (x == ex && y == ey) goto ANS;
				}
			}
		}
ANS:
		printf("%d\n", mat[ex][ey]);
	}
	return 0;
}



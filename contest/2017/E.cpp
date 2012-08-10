#include <stdio.h>
#include <string.h>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN = 300+5;
const int d[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1} };

struct Node {
	int x, y, c;
	Node(int tx, int ty, int tc):x(tx), y(ty), c(tc) {
	}
};
bool vis[MAXN][MAXN];

int bfs(int x1, int y1, int x2, int y2)
{
	queue<Node> Q;
	Q.push(Node(x1, y1, 0));
	memset(vis, 0, sizeof(vis));
	vis[x1][y1] = true;
	while (Q.empty() == false) {
		Node nd = Q.front();
		Q.pop();
		if (nd.x == x2 && nd.y == y2) {
			return nd.c;
		}
		for (int i = 0; i < 8; i++) {
			int x = nd.x + d[i][0], y = nd.y + d[i][1];
			if (0 <= x && x <= 300 && 0 <= y && y <= 300 && vis[x][y] ==false) {
				Q.push(Node(x, y, nd.c+1));
				vis[x][y] = true;
			}
		}
	}
	return 999999999;
}

int main()
{
	int x1, x2, y1, y2;
	while (EOF != scanf("%d %d %d %d", &x1, &y1, &x2, &y2)) {
		printf("%d\n", bfs(x1, y1, x2, y2));
	}
	return 0;
}


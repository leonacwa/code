#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int NN = 100+5;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
struct Node {
	int x, y, v, st;
	Node(int tx, int ty, int tv, int tst) : x(tx), y(ty), v(tv), st(tst)
	{}
};
bool used[NN][NN][100+1];
int x, sx, sy, n, m;
char mm[NN][NN];

int bfs(int sx, int sy, int x)
{
	queue<Node> que;
	memset(used, 0, sizeof(used));
	used[sx][sy][0] = true;
	que.push(Node(sx, sy, 0, 0));
	while (false == que.empty()) {
		Node tn = que.front();
		que.pop();
		for (int i = 0; i < 4; ++i) {
			int tx = tn.x + dx[i], ty = tn.y + dy[i], tv = tn.v;
			if (0 <= tx && tx < n && 0 <= ty && ty < m && mm[tx][ty] != '#') {
				if ( '0' <= mm[tx][ty] && mm[tx][ty] <= '9') {
					tv += mm[tx][ty] - '0';
				}
				if (tv == x) return tn.st + 1;
				if (tv < x && !used[tx][ty][tv]) {
					used[tx][ty][tv] = true;
					que.push(Node(tx, ty, tv, tn.st+1));
				}
			}
		}
	}
	return -1;
}

int main()
{
	int nCase;
	scanf("%d", &nCase);
	while (nCase--) {
		scanf("%d %d", &n, &m);
		++n, ++m;
		for (int i = 0; i < n; ++i) {
			scanf("%s", mm[i]);
			for (int j = 0; j < m; j++) {
				if (mm[i][j] == '*') {
					sx = i;
					sy = j;
				}
			}
		}
		scanf("%d", &x);
		if (x == 0) {
			puts("0");
		} else {
			printf("%d\n", bfs(sx, sy, x));
		}
	}
	return 0;
}


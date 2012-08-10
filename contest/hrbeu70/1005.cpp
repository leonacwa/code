#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <iostream>
using namespace std;

const int NN = 100 + 5;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int mm[NN][NN];
int mm_t[NN][NN];
int mm_t2[NN][NN];
int N, M, T;
int sx, sy;
int tot;

struct Node {
	int x, y, t;
	Node(int tx = 0, int ty = 0, int tt = 0) : x(tx), y(ty), t(tt)
	{}
};

void bfs_t()
{
	queue<Node> Q;
	Q.push(Node(sx, sy, 0));
	mm_t[sx][sy] = 0;
	while (!Q.empty()) {
		Node nod = Q.front();
		Q.pop();
		for (int i = 0; i < 4; ++i) {
			int x = nod.x + dx[i], y = nod.y + dy[i], t = nod.t + 1;
			if (0 <= x && x < N && 0 <= y && y < M && mm[x][y] != 2 &&  t < mm_t[x][y] && t <= T) {
				mm_t[x][y] = t;
				Q.push(Node(x, y, t));
			}
		}
	}
}

int bfs_m()
{
	queue<Node> Q;
	int ans = 0;
	Q.push(Node(sx, sy, 0));
	mm_t2[sx][sy] = 0;
	while (!Q.empty()) {
		Node nod = Q.front();
		Q.pop();
		for (int i = 0; i < 4; ++i) {
			int x = nod.x + dx[i], y = nod.y + dy[i], t = nod.t + 1;
			if (0 <= x && x < N && 0 <= y && y < M && mm[x][y] != 2 && 
				mm_t[x][y] < INT_MAX && t + mm_t[x][y] <= T && t < mm_t2[x][y]) {
				mm_t2[x][y] = t;
				if (mm[x][y] == 1) {
					mm[x][y] = 0;
					++ans;
					if (ans == tot) return ans;
				}
				Q.push(Node(x, y, t));
			}
		}
	}
	return ans;
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d %d", &N, &M, &T)) {
		tot = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				scanf("%d", &mm[i][j]);
				mm_t[i][j] = INT_MAX;
				mm_t2[i][j] = INT_MAX;
				if (mm[i][j] == 3) {
					sx = i;
					sy = j;
				} else if (mm[i][j] == 1) {
					tot++;
				}
			}
		}
		bfs_t();
		printf("Case %d:\n%d\n", ++nCase, bfs_m());
	}
	return 0;
}


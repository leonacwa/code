#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int MN = 1000 + 5;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

struct Pos {
	int x, y, d;
	Pos (int tx = 0, int ty = 0, int td = 0) : x(tx), y(ty), d(td)
	{}
};
char mm[MN][MN];
long cnt[MN][MN][4];
long dist[MN][MN][4];
int sx, sy, ex, ey, sd, r, c, modu;
int drt[256];

void addState(queue<Pos> &Q, Pos &cur, Pos &next)
{
	int l = dist[cur.x][cur.y][cur.d] + 1;
	if (dist[next.x][next.y][next.d] >= 0 && dist[next.x][next.y][next.d] < l) {
		return;
	}
	if (dist[next.x][next.y][next.d] == -1) {
		Q.push(next);
		dist[next.x][next.y][next.d] = l;
	}
	cnt[next.x][next.y][next.d] = (cnt[next.x][next.y][next.d] + cnt[cur.x][cur.y][cur.d]) % modu;
}

int bfs()
{
	queue<Pos> Q;

	memset(cnt, 0, sizeof(cnt));
	memset(dist, -1, sizeof(dist));

	Q.push(Pos(sx, sy, sd));
	cnt[sx][sy][sd] = 1;
	dist[sx][sy][sd] = 0;
	while (!Q.empty()) {
		Pos p1 = Q.front(), p2;
		Q.pop();
		if (p1.x == ex && p1.y == ey) {
			int ret = 0;
			for (int i = 0; i < 4; ++i) {
				if (dist[ex][ey][i]  == dist[ex][ey][p1.d]) {
					ret += cnt[ex][ey][i];
					ret %= modu;
				}
			}
			return ret;
		}
		p2 = p1;
		p2.d = (p2.d + 3) % 4;
		addState(Q, p1, p2);
		p2 = p1;
		p2.d = (p2.d + 1) % 4;
		addState(Q, p1, p2);
		p2 = p1;
		p2.x += dx[p2.d];
		p2.y += dy[p2.d];
		if (0 <= p2.x && p2.x < r && 0 <= p2.y && p2.y < c && mm[p2.x][p2.y] == '.') {
			addState(Q, p1, p2);
		}
	}
	return -1;
}

int main()
{
	char ch;
	int nCase = 0;
	drt['N'] = 0;
	drt['S'] = 2;
	drt['E'] = 1;
	drt['W'] = 3;
	while (EOF != scanf("%d %d %d", &r, &c, &modu) && modu != 0) {
		for (int i = 0; i < r; ++i) {
			scanf("%s", mm[i]);
		}
		scanf("%d %d %d %d %c", &sx, &sy, &ex, &ey, &ch);
		sd = drt[ch];
		printf("Case %d: %d %d\n", ++nCase, modu, bfs());
	}
	return 0;
}


/* Sheep Frenzy
 * 状态压缩DP
 * */
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

const int 
	dx[4] = {-1, 0, 1, 0},
	dy[4] = {0, 1, 0, -1};

int sheep_id[51][51];
char mat[51][51];
int vis[51][51];
int dis[17][17];
int f[1<<16][17];
bool inq[1<<16][17];

bool can_eat_all_sheep(int h, int w, int n, int sx, int sy) {
	memset(dis, -1, sizeof(dis));
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			if (mat[i][j] == '#' || mat[i][j] == 'U') {
				dis[sheep_id[i][j]][sheep_id[i][j]] = 0;
				memset(vis, -1, sizeof(vis));
				queue< pair<int, int> > que;
				que.push(make_pair(i, j));
				vis[i][j] = 0;
				while (!que.empty()) {
					pair<int, int> pt = que.front();
					que.pop();
					int step = vis[pt.first][pt.second];
					for (int k = 0; k < 4; ++k) {
						int x = pt.first + dx[k], y = pt.second + dy[k];
						if (0 <= x && x < h && 0 <= y && y < w && -1 == vis[x][y] && mat[x][y] != 'X') {
							que.push(make_pair(x, y));
							vis[x][y] = 1 + step;
							if (mat[x][y] == '#' || mat[x][y] == 'U') {
								dis[sheep_id[i][j]][sheep_id[x][y]] = vis[x][y];
							}
						}
					}
				}
				if (dis[sheep_id[i][j]][sheep_id[sx][sy]] == -1) return false;
			}
		}
	}
	return true;
}

int get_bit(int s) {
	int i = 0;
	while (s) {
		if (s&1) break;
		s >>= 1;
		++i;
	}
	return i;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int h, w, sx = -1, sy, sheep = 0;
		scanf("%d%d", &h, &w);
		memset(sheep_id, 0, sizeof(sheep_id));
		for (int i = 0; i < h; ++i) {
			scanf("%s", mat[i]);
			for (int j = 0; j < w; ++j) {
				if (mat[i][j] == 'U') sx = i, sy = j;
				if (mat[i][j] == '#') {
					sheep_id[i][j] = sheep;
					++sheep;
				}
			}
		}
		sheep_id[sx][sy] = sheep;
		if (!can_eat_all_sheep(h, w, sheep, sx, sy)) {
			puts("impossible");
			continue;
		}
		memset(f, -1, sizeof(f));
		memset(inq, 0, sizeof(inq));
		queue< pair<int, int> > que;
		int s = (1<<sheep) - 1;
		for (int i = 0; i < sheep; ++i) {
			//printf("s%d -> %d: %d\n", sheep, i, dis[sheep][i]);
			f[s ^ (1<<i)][i] = dis[sheep][i] + 1;
			que.push(make_pair(s ^ (1<<i), i));
			inq[s ^ (1<<i)][i] = true;
		}
		while (!que.empty()) {
			pair<int, int> pt = que.front();
			que.pop();
			//printf("q size %d\n", que.size());
			int os = pt.first, oi = pt.second;
			inq[os][oi] = false;
		//	printf("f os %d %d\n", os, oi);
			for (int ss = os, i, s; ss; ss ^= (1<<i)) {
				i = get_bit(ss);
				s = os ^ (1<<i);
				if (f[s][i] == -1 || f[s][i] > f[os][oi] + dis[oi][i] + 1) {
	//				printf("f %d %d\n", s, i);
					f[s][i] = f[os][oi] + dis[oi][i] + 1;
					if (!inq[s][i]) {
						que.push(make_pair(s, i));
						inq[s][i] = true;
					}
				}
			}
		}
		int ans = -1;
		for (int i = 0; i < sheep; ++i) {
			if (ans > f[0][i] || ans == -1) ans = f[0][i];
		}
		printf("%d\n", ans);
	}
	return 0;
}

#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
int r, c, si, sj, ti, tj, sd;
int opt[1005][1005][4];
bool used[1005][1005][4];
int MOD;
char mp[1005][1005];
char dir[10];
struct NODE {
	NODE(int xx, int yy, int dd) : x(xx), y(yy), d(dd) {}
	NODE() {}
	int x, y, d;
};
const int INF = 1000000000;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
void deal(int di, int dj, int dd, int ni, int nj, int nd, int opt[1005][1005][4], bool used[1005][1005][4], queue<NODE> &qu) {
	if (di >= 0 && dj >= 0 && di < r && dj < c && mp[di][dj] != '*' && !used[di][dj][dd]) {
		used[di][dj][dd] = true;
		opt[di][dj][dd] = opt[ni][nj][nd] + 1;
		qu.push(NODE(di, dj, dd));
	}
}
int bfs() {
	int k, ni, nj, nd;
	int di, dj, dd;
	NODE np(si, sj, sd);
	queue<NODE> qu;
	qu.push(np);
	memset(used, 0, sizeof(used));
	used[si][sj][sd] = 1;
	opt[si][sj][sd] = 0;
	while (!qu.empty()) {
		np = qu.front();
		qu.pop();
		ni = np.x, nj = np.y, nd = np.d;
		di = ni, dj = nj, dd = (nd + 1) % 4;
		deal(di, dj, dd, ni, nj, nd, opt, used, qu);
		di = ni, dj = nj, dd = (nd + 4 - 1) % 4;
		deal(di, dj, dd, ni, nj, nd, opt, used, qu);
		di = ni + dx[nd], dj = nj + dy[nd], dd = nd;
		deal(di, dj, dd, ni, nj, nd, opt, used, qu);
	}
	int ret = INF;
	for (k = 0; k < 4; k++) {
		if (used[ti][tj][k]) ret = min(ret, opt[ti][tj][k]);
	}
	if (ret < INF) {
		return ret;
	} else {
		return -1;
	}
}
bool cal[1005][1005][4];
int val[1005][1005][4];
int check(int ni, int nj, int nd) {
	if (ni >= 0 && nj >= 0 && ni < r && nj < c && mp[ni][nj] != '*' && used[ni][nj][nd]) {
		return 1;
	} else {
		return 0;
	}
}
int dfs(int ni, int nj, int nd) {
	if (cal[ni][nj][nd]) return val[ni][nj][nd];
	int di, dj, dd;
	int ret = 0;
	di = ni, dj = nj, dd = (nd + 1) % 4;
	if (check(di, dj, dd) && opt[di][dj][dd] + 1 == opt[ni][nj][nd]) {
		ret += dfs(di, dj, dd);
		ret %= MOD;
	}
	di = ni, dj = nj, dd = (nd + 4 - 1) % 4;
	if (check(di, dj, dd) && opt[di][dj][dd] + 1 == opt[ni][nj][nd]) {
		ret += dfs(di, dj, dd);
		ret %= MOD;
	}
	di = ni - dx[nd], dj = nj - dy[nd], dd = nd;
	if (check(di, dj, dd) && opt[di][dj][dd] + 1 == opt[ni][nj][nd]) {
		ret += dfs(di, dj, dd);
		ret %= MOD;
	}
	cal[ni][nj][nd] = true;
	val[ni][nj][nd] = ret;
	return ret;
}
int main() {
	int i, mind, id = 0, k;
	int ans;
	while (scanf("%d%d%d", &r, &c, &MOD) != EOF) {
		if (MOD == 0) break;
		id++;
		for (i = 0; i < r; i++) {
			scanf("%s", mp[i]);
		}
		scanf("%d%d%d%d%s", &si, &sj, &ti, &tj, dir);
		switch (dir[0]) {
		case 'N' :
			sd = 0;
			break;
		case 'E' :
			sd = 1;
			break;
		case 'S' :
			sd = 2;
			break;
		case 'W' :
			sd = 3;
			break;
		default :
			break;
		}
		mind = bfs();
		if (mind == -1) {
			printf("Case %d: %d -1\n", id, MOD);
			continue;
		}
		ans = 0;
		memset(cal, 0, sizeof(cal));
		cal[si][sj][sd] = true;
		val[si][sj][sd] = 1;
		for (k = 0; k < 4; k++) {
			if (used[ti][tj][k] && opt[ti][tj][k] == mind) {
				ans += dfs(ti, tj, k);
				ans %= MOD;
			}
		}
		printf("Case %d: %d %d\n", id, MOD, ans);
	}
	return 0;
}
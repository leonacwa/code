/* D. Snake
 * */
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <map>
using namespace std;

typedef unsigned int uint;

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
const int MAXN = 16;

struct Node {
	int h, stp;
	int p[9][2];
};
char mat[MAXN][MAXN];
int used[MAXN][MAXN];

uint Hash(int k, const Node &d) {
	uint seed = 131;
	uint ret = 0;
	for (int i = 0; i < k; ++i) {
		int j = (d.h + i) % k;
		ret = ret * seed + d.p[j][0] * 16 + d.p[j][1];
	}
	return ret;
}

int main() {
	int n, m, k;
	while (EOF != scanf("%d%d", &n, &m)) {
		Node fir;
		k = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", mat[i]);
			for (int j = 0; j < m; ++j) {
				if ('0' <= mat[i][j] && mat[i][j] <= '9') {
					int t = mat[i][j] - '1';
					fir.p[t][0] = i;
					fir.p[t][1] = j;
					if (k < t+1) k = t + 1;
				}
			}
		}
		fir.h = 0;
		fir.stp = 0;
		queue<Node> que;
		set<uint> ss;
		int go = 0;
		que.push(fir);
		ss.insert(Hash(k, fir));
		int ans = -1;
		while (!que.empty()) {
			Node now = que.front();
			que.pop();
			++go;
			for (int i = 0; i < k-1; ++i) {
				int j = (now.h + i) % k;
				used[now.p[j][0]][now.p[j][1]] = go;
			}
			for (int i = 0; i < 4; ++i) {
				int x = now.p[now.h][0] + dx[i], y = now.p[now.h][1] + dy[i];
				if (0 <= x && x < n && 0 <= y && y < m && mat[x][y] != '#' && used[x][y] != go) {
					if (mat[x][y] == '@') {
						ans = now.stp + 1;
						goto  Answer;
					}
					Node nxt = now;
					nxt.h = (nxt.h - 1 + k) % k;
					nxt.p[nxt.h][0] = x;
					nxt.p[nxt.h][1] = y;
					nxt.stp++;
					uint id = Hash(k, nxt);
					set<uint>::iterator it = ss.find(id);
					if (it == ss.end()) {
						ss.insert(id);
						que.push(nxt);
					}
				}
			}
		}
Answer:
		printf("%d\n", ans);
	}
	return 0;
}

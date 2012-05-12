#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1000+5;
const int INF = 999999999;

struct Node {
	int v, g, f; // fi = gi + dis[i]
	Node (int tv, int tg, int tf): v(tv), g(tg), f(tf) {
	}
	bool operator < (const Node& b) const {
		if (f == b.f) return g > b.g;
		return f > b.f;
	}
};

int g[MAXN][MAXN];
int dis[MAXN];
bool v[MAXN];
int m;

void init()
{
	for (int i = 0; i < m; i++) {
		dis[i] = INF;
		v[i] = false;
	}
	dis[m-1] = 0;
	for (int i = 0; i < m; i++) {
		int min_d = INF;
		int k = -1;
		for (int j = 0 ; j < m; j++) {
			if (false == v[j] && min_d > dis[j]) {
				min_d = dis[j];
				k = j;
			}
		}
		if (k == -1) {
			break;
		}
		v[k] = true;
		for (int j = 0; j < m; j++) {
			if (false == v[j] && g[j][k] < INF && dis[j] > min_d + g[j][k]) {
				dis[j] = min_d + g[j][k];
			}
		}
	}
}

int k_short()
{
	init();
	priority_queue<Node> Q;
	Q.push(Node(0, 0, dis[0]));
	int cnt = 0;
	while (false == Q.empty()) {
		Node node = Q.top();
		Q.pop();
		if (node.v == m-1) {
			cnt++;
		}
		if (cnt == 2) {
			return node.g;
		}
		if (cnt > 2) {
			return INF;
		}
		for (int i = 0; i < m; i++) {
			if (g[node.v][i] < INF) {
				Q.push(Node(i, node.g + g[node.v][i], node.g + g[node.v][i] + dis[i]));
			}
		}
	}
	return INF;
}

int main()
{
	while (EOF != scanf("%d", &m)) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				g[i][j] = INF;
			}
		}
		for (int i = 0; i < m; i++) {
			int n;
			scanf("%d", &n);
			for (int j = 0; j < n; j++) {
				int a, w;
				scanf("%d %d", &a, &w);
				g[i][a-1] = min(g[i][a-1], w);
			}
		}
		for (int i = 0; i < m; i++) {
			dis[i] = INF;
		}
		printf("%d\n", k_short());
	}
	return 0;
}

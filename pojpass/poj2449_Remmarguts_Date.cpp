#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1005;
const int MAXM = 100005;

struct Edge {
	int v, w, next;
};
Edge Es[2][MAXM];
int ve[2][MAXN];
int e_cnt[2];
int dis[MAXN];
bool vis[MAXN];
int S, T, K, N, M;

struct Node {
	int v, f, g;
	Node(int tv, int tf, int tg):v(tv), f(tf), g(tg) {
	}
	bool operator < (const Node&b) const {
		if (f == b.f) return g > b.g;
		return f > b.f;
	}
};

void add_edge(int ar, int a, int b, int w)
{
	Es[ar][e_cnt[ar]].v = b;
	Es[ar][e_cnt[ar]].w = w;
	Es[ar][e_cnt[ar]].next = ve[ar][a];
	ve[ar][a] = e_cnt[ar];
	e_cnt[ar]++;
}

void init()
{
	memset(dis, 0x3f, sizeof(dis));
	dis[T] = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < N; i++) {
		int min_d = INF;
		int k = -1;
		for (int j = 1; j <= N; j++) {
			if (false == vis[j] && min_d > dis[j]) {
				min_d = dis[j];
				k = j;
			}
		}
		if (k == -1) {
			break;
		}
		vis[k] = true;
		for (int ne = ve[1][k]; ne != -1; ne = Es[1][ne].next) {
			int v = Es[1][ne].v;
			int w = Es[1][ne].w;
			if (false == vis[v] && dis[v] > min_d + w) {
				dis[v] = min_d + w;
			}
		}
	}
}

int k_short_path()
{
	init();
	priority_queue<Node> Q;
	Q.push(Node(S, dis[S], 0));
	int cnt = 0;
	while (false == Q.empty()) {
		Node nd = Q.top();
		Q.pop();
		if (nd.v == T) {
			cnt++;
		}
		if (cnt == K) {
			return nd.g;
		}
		for (int ne = ve[0][nd.v]; ne != -1; ne = Es[0][ne].next) {
			Q.push(Node(Es[0][ne].v, nd.g + Es[0][ne].w + dis[Es[0][ne].v], nd.g + Es[0][ne].w));
		}
	}
	return -1;
}

int main()
{
	while (EOF != scanf("%d %d", &N, &M)) {
		memset(ve, -1, sizeof(ve));
		e_cnt[0] = e_cnt[1] = 0;
		for (int i = 0; i < M; i++) {
			int a, b, w;
			scanf("%d %d %d", &a, &b, &w);
			add_edge(0, a, b, w);
			add_edge(1, b, a, w);
		}
		scanf("%d %d %d", &S, &T, &K);
		if (S == T) {
			K++; //???????
		}
		printf("%d\n", k_short_path());
	}	   
	return 0;
}


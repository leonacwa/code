/* Dinic, Max Flow */

#include <stdio.h>
#include <string.h>

const int INT_MAX = -1u>>1;
const int MAXN = 400+5;
int c[MAXN][MAXN];
int J, M;
int src, sink;

int d[MAXN];
int Q[MAXN*2];
int head, tail;

bool bfs()
{
	memset(d, -1, sizeof(d));
	head = 0;
	tail = 1;
	Q[head] = sink;
	d[sink] = 0;
	while (head < tail) {
		int v = Q[head++];
		for (int u = 0; u <= sink; u++) {
			if (d[u] == -1 && c[u][v] > 0) {
				d[u] = d[v] + 1;
				Q[tail++] = u;
			}
		}
		if (d[src] != -1) {
			return true;
		}
	}
	return false;
}

int dinic(int u, int flow)
{
	if (u == sink) {
		return flow;
	}
	int send = 0;
	for (int v = 0; v <= sink; v++) {
		if (flow > 0 && c[u][v] > 0 && d[u] == d[v] + 1) {
			int a = dinic(v, flow<c[u][v]?flow:c[u][v]);
			c[u][v] -= a;
			c[v][u] += a;
			flow -= a;
			send += a;
		}
	}
	return send;
}

int max_flow()
{
	int flow = 0;
	while (bfs()) {
		flow += dinic(src, INT_MAX);
	}
	return flow;
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &J, &M);
		src = 0;
		memset(c, 0, sizeof(c));
		int max_d = 0;
		int work = 0;
		for (int i = 1; i <= J; i++) {
			int p, r, d;
			scanf("%d %d %d", &p, &r, &d);
			work += p;
			if (max_d < d) {
				max_d = d;
			}
			c[src][i] = p;
			for (int j = r; j <= d; j++) {
				c[i][J+j] = 1;
			}
		}
		sink = J + max_d + 1;
		for (int i = J+1; i <= J+max_d; i++) {
			c[i][sink] = M;
		}
		int max_val = max_flow();
		if (max_val == work) {
		   printf("Boss xnby is happy!\n");
		} else {
			printf("Boss xnby is angry!\n");
		}		
	}
	return 0;
}


/* Push&Relabel, Max Flow */

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

const int INT_MAX = -1u>>1;
const int MAXN = 400+5;
int c[MAXN][MAXN];
int J, M;
int src, sink;
int e[MAXN]; // excess flow
int h[MAXN]; // height of vertex

void init_pre_flow()
{
	memset(e, 0, sizeof(e));
	memset(h, 0, sizeof(h));
	h[src] = sink+1;
	for (int u = 0; u <= sink; u++) {
		if (src != u && c[src][u] > 0) {
			e[u] += c[src][u];
			e[src] -= c[src][u];
			c[u][src] += c[src][u];
			c[src][u] -= c[src][u];
		}
	}
}

void push(int u, int v)
{
	int d = min(e[u], c[u][v]);
	e[u] -= d;
	e[v] += d;
	c[u][v] -= d;
	c[v][u] += d;
}

bool relabel(int u)
{
	int cnt = 0, h_cnt = 0, min_h = INT_MAX;// max height 2*(sink+1) is ok
	for (int v = 0; v <= sink; v++) {
		if (c[u][v] > 0) {
			cnt++;
			if (h[u] <= h[v]) {
				h_cnt++;
				min_h = min(min_h, h[v]);
			}
		}
	}
	if (cnt > 0 && cnt == h_cnt) {
		h[u] = min_h + 1;
		return true;
	}
	return false;
}

int max_flow()
{
	bool push_relabel = true;
	init_pre_flow();
	while (push_relabel) {
		push_relabel = false;
		for (int u = 0; u < sink; u++) { // Source ans Sink can not send sny flow !!!!!!!!
			if (e[u] > 0) {
				if (relabel(u)) {
					push_relabel = true;
				}
				for (int v = 0; v <= sink; v++) {
					if (c[u][v] > 0 && h[v]+1 == h[u]) {
						push(u, v);
						push_relabel = true;
					}
				}
			}
		}
	}
	return e[sink];
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


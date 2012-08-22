#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 101;
const int INF = INT_MAX / 200;
struct Edge {
	int v;
	struct Edge * next;
};
Edge E[NN*2];
int E_ct, n;
Edge *head[NN];
int f[NN][3];

void addEdge(int u, int v)
{
	Edge *ptr = &E[E_ct++];
	ptr->v = v;
	ptr->next = head[u];
	head[u] = ptr;
}

void dp(int r, int pr)
{
	if (head[r] == NULL) {
		f[r][0] = INF;
		f[r][1] = 0;
		f[r][2] = INF;
		return;
	}
	int sum_c0 = 0;
	for (Edge *cur = head[r]; cur; cur = cur->next) {
		int c = cur->v;
		if (c != pr) {
			dp(c, r);
			sum_c0 += f[c][0];
		}
	}
	f[r][0] = INF;
	f[r][1] = sum_c0;
	f[r][2] = INF;
	for (Edge *cur = head[r]; cur; cur = cur->next) {
		int c = cur->v;
		if (c != pr) {
			f[r][0] = min(f[r][0], sum_c0 - f[c][0] + f[c][2] + 1);
			f[r][2] = min(f[r][2], sum_c0 - f[c][0] + min(f[c][1], f[c][2]));
		}
	}
	for (Edge *cur1 = head[r]; cur1; cur1 = cur1->next) {
		int c1 = cur1->v;
		for (Edge *cur2 = head[r]; cur2; cur2 = cur2->next) {
			int c2 = cur2->v;
			if (c1 != c2 && c1 != pr && c2 != pr) {
				f[r][0] = min(f[r][0], 
						sum_c0 - f[c1][0] - f[c2][0] + min(f[c1][1], f[c1][2]) + min(f[c2][1], f[c2][2]) + 1);
			}
		}
	}
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		memset(head, 0, sizeof(head));
		E_ct = 0;
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
		}
		dp(1, -1);
		if (f[1][0] >= INF) {
			puts("-1");
		} else {
			printf("%d\n", f[1][0]);
		}
	}
	return 0;
}


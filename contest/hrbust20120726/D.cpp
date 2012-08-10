#include <cstdio>
#include <cstring>

const int MAXN = 505;

struct Edge {
	int to;
	int next;
	Edge(int tto=0, int tn=0) : to(tto), next(tn) {}
} E[MAXN * MAXN];
int nE, V[MAXN];
int m1[MAXN], m2[MAXN];

void addEdge(int u, int v) {
	E[nE] = Edge(v, V[u]);
	V[u] = nE++;
}

/* hungary 算法 */
int maxmatch(int n1, int n2) { /* BFS找增广路 */
	int p, q, s[MAXN], t[MAXN], ret = 0, i, j, k, l;
	memset(m1, -1, sizeof(m1[0])*n1);
	memset(m2, -1, sizeof(m2[0])*n2);
	for (i = 0; i < n1; ++i) {
		memset(t, -1, sizeof(t[0])*n2);
		for (s[p=q=0] = i; p <= q && m1[i] < 0 ; ++p) {
			for (k = s[p], l = V[k]; l != -1 && m1[i] < 0; l = E[l].next) {
				j = E[l].to;
				if (t[j] < 0) {
					s[++q] = m2[j], t[j] = k;
					if (s[q] < 0) {
						for (p = j; p >= 0; j = p) {
							m2[j] = k = t[j];
							p = m1[k];
							m1[k] = j;
						}
					}
				}
			}
		}
		if (m1[i] >= 0) ++ret;
	}
	return ret;
}

int main()
{
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		for (int i = 0; i <= n; ++i) V[i] = -1;
		nE = 0;
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			addEdge(a, b);
		}
		printf("%d\n", n - maxmatch(n, n));
	}
	return 0;
}


/* 
 * zoj 3545 Rescue the Rabbit 
 * */

#include <stdio.h>
#include <string.h>

#define MAXNODES 1024
#define MAXDNAS 16
#define DNA 4

int node[MAXNODES][4];
int fail[MAXNODES], word[MAXNODES];
int root, node_sz;

int get_id(char ch)
{
	switch (ch) {
		case 'A': return 0;
		case 'T': return 1;
		case 'G': return 2;
		case 'C': return 3;
	}
	return -1;
}

void init()
{
	memset(&node[0], -1, sizeof(int)*DNA);
	root = 0;
	word[0] = 0;
	node_sz = 1;
}

void insert(char *s, int id)
{
	int i, p;
	p = root;
	for (; *s; ++s) {
		i = get_id(*s);
		if (node[p][i] == -1) {
			memset(node[node_sz], -1, sizeof(int)*DNA);
			word[node_sz] = 0;
			fail[node_sz] = -1;
			node[p][i] = node_sz++;
		}
		p = node[p][i];
	}
	word[p] |= (1 << id);
}

int Q[MAXNODES];

void ac()
{
	int i, p, v, front = 0, rear = 0;	
	for (i = 0; i < DNA; ++i) {
		if (node[root][i] != -1) {
			fail[node[root][i]] = root;
			Q[rear++] = node[root][i];
		}
		else
			node[root][i] = root;
	}
	while (front < rear) {
		p = Q[front++];
		for (i = 0; i < DNA; ++i) {
			if (node[p][i] != -1) {
				v = node[p][i];
				Q[rear++] = v;
				fail[v] = node[fail[p]][i];
				word[v] |= word[fail[v]];
			}
			else 
				node[p][i] = node[fail[p]][i];
		}
	}
}

char dp[2][MAXNODES][MAXNODES];

int main() 
{
	int i, j, k, now, next, id, mask, score[MAXDNAS];
	int n, l, ch, w, ans, sum;
	char str[256];
	while (2 == scanf("%d %d", &n, &l)) {
		init();
		id = -1;
		for (i = 0; i < n; ++i) {
			scanf("%s %d", str, &w);
			if (strlen(str) <= l) {
				insert(str, ++id);
				score[id] = w;
			}
		}
		ac();
		mask = 1 << n;
		memset(dp, 0, sizeof(dp));
		dp[0][0][0] = 1;
		for (i = 0; i < l; ++i) {
			now = i % 2;
			next = (i+1) % 2;
			memset(dp[next], 0, sizeof(dp[next]));
			for (j = 0; j < node_sz; ++j) {
				for (k = 0; k < mask; ++k) {
					for (ch = 0; ch < DNA; ++ch) {
						if (dp[now][j][k]) {
							dp[next][node[j][ch]][k|word[node[j][ch]]] = 1;
						}
					}
				}
			}
		}
		now = l % 2;
		ans = -99999999;
		for (i = 0; i < node_sz; ++i) {
			for (j = 0; j < mask; ++j) {
				if (dp[now][i][j]) {
					sum = 0;
					for (k = 0; k <= id; ++k) {
						if (j & (1<<k))
							sum += score[k];
					}
					if (sum > ans) ans = sum;
				}
			}
		}
		if (ans >= 0) printf("%d\n", ans);
		else puts("No Rabbit after 2012!");
	}
	return 0;
}







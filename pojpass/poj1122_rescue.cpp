#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 21;
int n, cnt, dst;
int mat[NN][NN];
int src[NN];
int len[NN];
int pre[NN];
bool vis[NN];

bool cmpsrc(const int &a, const int &b)
{
	if (len[a] == len[b]) return a < b;
	return len[a] < len[b];
}

void dijkstra(int s)
{
	for (int i = 0; i < n; ++i) {
		len[i] = mat[s][i];
		pre[i] = s;
		vis[i] = false;
	}
	len[s] = 0;
	pre[s] = -1;
	for (int i = 0; i < n; ++i) {
		int minLen = INT_MAX;
		int u = -1;
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && len[j] != -1 && minLen > len[j]) {
				minLen = len[j];
				u = j;
			}
		}
		if (u == -1) break;
		vis[u] = true;
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && mat[u][j] != -1 && (len[j] == -1 || len[j] > minLen + mat[u][j])) {
				len[j] = minLen + mat[u][j];
				pre[j] = u;
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d", &mat[j][i]);
		}
	}
	scanf("%d", &dst);
	--dst;
	cnt = 0;
	while (EOF != scanf("%d", &src[cnt])) {
		--src[cnt];
		++cnt;
	}
	dijkstra(dst);
	sort(src, src + cnt, cmpsrc);
	printf("Org\tDest\tTime\tPath\n");
	for (int i = 0; i < cnt; ++i) {
		printf("%d\t%d\t%d", src[i] + 1, dst + 1, len[src[i]]);
		int p = src[i];
		while (p != -1) {
			printf("\t%d", p + 1);
			p = pre[p];
		}
		printf("\n");
	}
	return 0;
}


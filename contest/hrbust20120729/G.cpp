#include <cstdio>
#include <cstring>

const int MAXN = 1001;
bool mat[MAXN][MAXN];
bool vis[MAXN];
int ord[MAXN];
bool tv[MAXN], uv[MAXN];
int n;

void udfs(int u) {
	uv[u] = true;
	for (int i = 0; i < MAXN; ++i) {
		if (mat[u][i] && !uv[i]) {
			udfs(i);
		}
	}
}

void tdfs(int u) {
	tv[u] = true;
	for (int i = 0; i < MAXN; ++i) {
		if (mat[i][u] && !tv[i]) {
	//		printf("%d %d %d \n", i, u, mat[i][u]);
			tdfs(i);
		}
	}
}


int main()
{
	while (EOF != scanf("%d", &n)) {
		memset(mat, 0, sizeof(mat));
		for (int i = 0, f, s, t; i < n; ++i) {
			scanf("%d%d", &f, &s);
			ord[i] = f;
			while (s--) {
				scanf("%d", &t);
				mat[f][t] = true;
			}
		}
		memset(tv, 0, sizeof(tv));
		memset(uv, 0, sizeof(uv));
		udfs(0);
		tdfs(0);
		bool find = false;
		for (int i = 0; i < n; ++i) {
			if (!tv[ord[i]]) {
				find = true;
				printf("TRAPPED %d\n", ord[i]);
			}
		}
		for (int i = 0; i < n; ++i) {
			if (!uv[ord[i]]) {
				find = true;
				printf("UNREACHABLE %d\n", ord[i]);
			}
		}
		if (find == false) puts("NO PROBLEMS");

	}
	return 0;
}

/* Supervisor, Supervisee
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 15, INF = 9999999;

int mat[MAXN][MAXN];
int nx, ny, mx[MAXN], my[MAXN];
int lx[MAXN], ly[MAXN], slack[MAXN];
int _FLAG, vx[MAXN], vy[MAXN];

bool KM_dfs(int x) {
	vx[x] = _FLAG;
	for (int y = 0; y < ny; ++y) {
		if (vy[y] == _FLAG) continue;
		int t = lx[x] + ly[y] - mat[x][y];
		if (t == 0) {
			vy[y] = _FLAG;
			if (my[y] == -1 || KM_dfs(my[y])) {
				mx[x] = y;
				my[y] = x;
				return true;
			}
		} else if (slack[y] > t) {
			slack[y] = t;
		}
	}
	return false;
}

int KM() {
	_FLAG = 0;
	for (int i = 0; i < nx; ++i) {
		mx[i] = -1;
		vx[i] = -1;
		lx[i] = -INF;
		for (int j = 0; j < ny; ++j) {
			if (lx[i] < mat[i][j]) lx[i] = mat[i][j];
		}
	}
	for (int i = 0; i < ny; ++i) {
		my[i] = -1;
		vy[i] = -1;
		ly[i] = 0;
	}
	for (int i = 0; i < ny; ++i) {
		for (int j = 0; j < ny; ++j) slack[j] = INF;
		++_FLAG;
		while (!KM_dfs(i)) {
			int d = INF;
			for (int j = 0; j < ny; ++j) if (vy[j] != _FLAG && d > slack[j]) d = slack[j];
			for (int j = 0; j < nx; ++j) if (vx[j] == _FLAG) lx[j] -= d;
			for (int j = 0; j < ny; ++j) if (vy[j] == _FLAG) ly[j] += d;
			++_FLAG;
		}
	}
	int ret = 0;
	for (int i = 0; i < ny; ++i) {
		if (my[i] != -1) ret += mat[my[i]][i];
	}
	return ret;
}

int best_cnt, ans;
void dfs(int x, int sum) {
	if (sum > ans) return;
	if (x >= nx) {
		if (sum != ans) return;
		printf("Best Pairing %d\n", ++best_cnt);
		for (int i = 0; i < nx; ++i) {
			printf("Supervisor %d with Employee %d\n", i+1, mx[i]+1);
		}
	}
	for (int i = 0; i < ny; ++i) {
		if (!vy[i]) {
			vy[i] = 1;
			mx[x] = i;
			dfs(x+1, sum - mat[x][i]);
			vy[i] = 0;
		}
	}
}

int main() {
	int runs;
	scanf("%d", &runs);
	for (int run = 1; run <= runs; ++run) {
		int n;
		scanf("%d", &n);
		memset(mat, 0, sizeof(mat));
		for (int i = 0, s; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &s);
				mat[s-1][i] -= j;
			}
		}
		for (int i = 0, e; i < n; ++i) {
			for (int j = 0;j < n; ++j) {
				scanf("%d", &e);
				mat[i][e-1] -= j;
			}
		}
		nx = ny = n;
		ans = -KM();
		printf("Data Set %d, Best average difference: %.6f\n", run, ans * 0.5 / n);
		memset(vy, 0, sizeof(vy));
		best_cnt = 0;
		dfs(0, 0);
		if (run < runs) puts("");
	}
	return 0;
}

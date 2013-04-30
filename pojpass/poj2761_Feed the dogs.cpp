/*
 * POJ 2761 Feed the dogs
 * 划分树解法
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005, LOG_N = 20;

int sorted[MAXN];
int val[LOG_N][MAXN];
int left[LOG_N][MAXN];

void make_tree(int L, int R, int d) {
	if (L == R) {
		left[d][L] = 1;
		return;
	}
	if (L > R) return;
	int M = (L + R) >> 1;
	int lsame = M - L + 1;
	for (int i = L; i <= R; ++i) {
		if (val[d][i] < sorted[M]) --lsame;
	}
	int lp = L, rp = M + 1;
	for (int i = L; i <= R; ++i) {
		left[d][i] = L == i ? 0 : left[d][i-1];
		if (val[d][i] < sorted[M]) {
			left[d][i]++;
			val[d+1][lp++] = val[d][i];
		} else if (val[d][i] > sorted[M]) {
			val[d+1][rp++] = val[d][i];
		} else {
			if (lsame > 0) {
				lsame--;
				left[d][i]++;
				val[d+1][lp++] = val[d][i];
			} else {
				val[d+1][rp++] = val[d][i];
			}
		}
	}
	make_tree(L, M, d+1);
	make_tree(M+1, R, d+1);
}

int query(int L, int R, int d, int l, int r, int k) {
	if (l == r) return val[d][l];
	int M = (L + R) >> 1;
	int ls1 = (L < l ? left[d][l-1] : 0);
	int ls2 = left[d][r] - ls1;
	if (ls2 >= k) {
		return query(L, M, d+1, L+ls1, L+ls1+ls2-1, k);
	} else {
		int lr1 = l - L - ls1;
		int lr2 = r+1-l - ls2;
		return query(M+1, R, d+1, M+1+lr1, M+lr1+lr2, k - ls2);
	}
}

void init(int n) {
	for (int i = 1; i <= n; ++i) sorted[i] = val[0][i];
	sort(sorted+1, sorted+1+n);
	make_tree(1, n, 0);
}

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; ++i) scanf("%d", &val[0][i]);
		init(n);
		while (m--) {
			int i, j, k;
			scanf("%d%d%d", &i, &j, &k);
			printf("%d\n", query(1, n, 0, i, j, k));
		}
	}
	return 0;
}

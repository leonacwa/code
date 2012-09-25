#include <cstdio>
#include <cstring>

typedef long long int64;

const int N = 100005;
int f[N];
int64 sum[N];
int nf;
int a[N];
int a_cnt;

bool dfs(int k, int i, int s, int pf) {
	if (i == -1 || s > sum[i]) return false;
	for (; i >= 0; --i) {
		if (f[i] >= pf) continue;
		if (f[i] < s) {
			a[k] = f[i];
			if (dfs(k+1, i-1, s - f[i], f[i])) return true;
		} else if (s == f[i]) {
			a[k] = f[i];
			a_cnt = k + 1;
			return true;
		}
	}
	return false;
}

int main() {
	int s, k;
	while (EOF != scanf("%d%d", &s, &k)) {
		//while (k == 1) ;
		f[0] = f[1] = 1;
		sum[0] = 1, sum[1] = 2;
		for (nf = 2; ; ++nf) {
			f[nf] = 2 * f[nf-1];
			if (nf > k) f[nf] -= f[nf-k-1];
			sum[nf] = sum[nf-1] + f[nf];
			if (f[nf] >= s) break;
		}
		a_cnt = 0;
		dfs(0, nf, s, f[nf]+1);
		printf("%d\n0", a_cnt+1);
		for (int i = 0; i < a_cnt; ++i) printf(" %d", a[i]);
		puts("");
	}
	return 0;
}

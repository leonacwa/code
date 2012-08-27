/* HDU 4268 Covered Walkway
 * 斜率优化DP，将N^2优化为N
 * */
#include <cstdio>

typedef long long int64;

const int MAXN = 1000005;

int q[MAXN];
int64 f[MAXN];
int64 x[MAXN];

#define SQ(x) ((x) * (x))

inline double G(int j, int i) {
	return (double)(f[j] - f[i] + x[j+1]*x[j+1] - x[i+1]*x[i+1]) / (2.0 * (x[j+1] - x[i+1]));
}

int read_int(int *x) { // 输入外挂,只能输入非负数
	int ch;
    while (EOF != (ch = getchar())) {
		if ('0' <= ch && ch <= '9') break;
	}
	if (EOF == ch) return EOF;
	*x = 0;
	while ('0' <= ch && ch <= '9') {
		*x = *x * 10 + ch - '0';
		ch = getchar();
	}
	return *x;
}

int main() {
	int n, c;
	while (EOF != scanf("%d%d", &n, &c) && n && c) {
		for (int i = 1, t; i <= n; ++i) {
			//scanf("%d", &t);
			read_int(&t);
			x[i] = t;
		}
		int fr = 0, ta = 1;
		q[0] = 0, f[0] = 0;
		for (int i = 1; i <= n; ++i) {
			while (fr+1 < ta && G(q[fr+1], q[fr]) <= x[i]) ++fr;
			f[i] = f[q[fr]] + c + SQ(x[i] - x[q[fr]+1]);
			while (fr < ta-1 && G(i, q[ta-1]) <= G(q[ta-1], q[ta-2])) --ta;
			q[ta++] = i;
		}
		printf("%lld\n", f[n]);
	}
	return 0;
}

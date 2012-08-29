/* HDU 2993 MAX Average Problem
 * 斜率优化
 * */
#include <cstdio>
typedef long long int64;

const int MAXN = 100005;

int q[MAXN];
int64 s[MAXN];

int64 cross(int64 x1, int64 y1, int64 x2, int64 y2) {
	return x1 * y2 - x2 * y1;
}

int read_int(int *x) {
	int ch;
	while (EOF != (ch = getchar()) && ('0' > ch || ch > '9')) ;
	if (ch == EOF) return EOF;
	*x = 0;
	while ('0' <= ch && ch <= '9') {
		*x *= 10;
		*x += ch - '0';
		ch = getchar();
	}
	return 1;
}

int main() {
	int n, k;
	while (EOF != scanf("%d%d", &n, &k)) {
		s[0] = 0;
		for (int i = 1; i <= n; ++i) {
			int t;
			read_int(&t);
			s[i] = s[i-1] + t;
		}
		int fr = 0, ta = 0;
		double ans = 0.0;
		for (int i = k; i <= n; ++i) { // 单调队列里维护的应该是可以选择的决策点，虽然不一定是最优点
			int j = i - k;
			while (fr<ta-1 && cross(q[ta-1]-q[ta-2], s[q[ta-1]]-s[q[ta-2]], j-q[ta-2], s[j]-s[q[ta-2]]) <= 0) {
				--ta;
			}
			q[ta++] = j;
			while (fr+1<ta && (s[i]-s[q[fr+1]])*(i-q[fr]) >= (s[i]-s[q[fr]])*(i-q[fr+1])) {
				++fr;
			}
			double t = (double)(s[i] - s[q[fr]]) / (i - q[fr]);
			if (ans < t) ans = t;
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}

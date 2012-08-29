/* HDU 3507 Print Article
 * 斜率优化
 * f[i] = Min(f[j] + M + (s[i] - s[j])^2) = M + s[i]^2 + Min(f[j] + s[j]^2 - 2*s[j]*s[i])
 * 设A:G = f[j] + s[j]^2 - 2*s[j]*s[i]，转化成 B:f[j] + s[j]^2 = 2*s[i] * s[j] + G
 * 要使得G最小，则在B中G最小，即直线B与y轴的交点最低，这样我们就需要维护一个下凸壳
 * */
#include <cstdio>
#include <cstring>

typedef long long int64;

const int MAXN = 500005;

int64 s[MAXN], f[MAXN];
int q[MAXN];

int64 cross(int64 x1, int64 y1, int64 x2, int64 y2) {
	return x1 * y2 - x2 * y1;
}

template <class T>
int read_num(T *x) {
	int ch;
	while (EOF != (ch = getchar()) && ('0' > ch || ch > '9')) ;
	if (EOF == ch) return EOF;
	*x = 0;
	while ('0' <= ch && ch <= '9') {
		*x *= 10;
		*x += ch - '0';
		ch = getchar();
	}
	return 1;
}

#define SQ(x) ((x)*(x))

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		s[0] = 0;
		for (int i = 1; i <= n; ++i) {
			read_num(&s[i]);
			s[i] += s[i-1];
		}
		int fr = 0, ta = 1;
		f[0] = 0;
		q[0] = 0;
		for (int i = 1; i <= n; ++i) {
			while (fr+1<ta && (f[q[fr+1]]+SQ(s[q[fr+1]])-f[q[fr]]-SQ(s[q[fr]])) <= s[i]*2*(s[q[fr+1]]-s[q[fr]])){
				++fr;
			}
			f[i] = f[q[fr]] + m + SQ(s[i] - s[q[fr]]);
			while (fr<ta-1 && 
					cross(
						s[i]-s[q[ta-1]], f[i]+SQ(s[i])-f[q[ta-1]]-SQ(s[q[ta-1]]), 
						s[q[ta-2]]-s[q[ta-1]], f[q[ta-2]]+SQ(s[q[ta-2]])-f[q[ta-1]]-SQ(s[q[ta-1]])
					   	) <= 0)
		   	{
				--ta;
			}
			q[ta++] = i;
		}
		printf("%lld\n", f[n]);
	}
	return 0;
}

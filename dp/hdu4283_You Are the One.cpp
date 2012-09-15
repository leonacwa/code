/* HDU 4283 You Are the One
 * 区间DP
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 105;

int f[MAXN][MAXN];
int D[MAXN], S[MAXN];

template <class T>
int read_num(T *x) {
	int ch;
	bool sign = 0;
	while (EOF != (ch = getchar()) && ('0' > ch || ch > '9') && ch != '-') ;
	if (EOF == ch) return EOF;
	if (ch == '-') {
		sign = 1;
		ch = getchar();
	}
	*x = 0;
	while ('0' <= ch && ch <= '9') {
		*x *= 10;
		*x += ch - '0';
		ch = getchar();
	}
	if (sign) *x = -*x;
	return 1;
}

int main() {
	int runs;
	//scanf("%d", &runs);
	read_num(&runs);
	for (int run = 1; run <= runs; ++run) {
		int n;
		D[0] = 0, S[0] = 0;
		//scanf("%d", &n);
		read_num(&n);
		for (int i = 1; i <= n; ++i) {
			//scanf("%d", &D[i]);
			read_num(D+i);
			S[i] = S[i-1] + D[i];
		}
		memset(f, 0x3f, sizeof(f));
		for (int i = 1; i <= n; ++i) f[i][i] = 0;
		for (int l = 1; l < n; ++l) {
			for (int i = 1; i+l <= n; ++i) {
				int j = i + l;
				f[i][j] = min(f[i+1][j] + S[j] - S[i], f[i+1][j] + l * D[i]);
				for (int k = 1; k < l; ++k) {
					f[i][j] = min(f[i][j], f[i+1][i+k] + f[i+k+1][j] + (k+1) * (S[j] - S[i+k])+ k * D[i]);
				}
			}
		}
		printf("Case #%d: %d\n", run, f[1][n]);
	}
	return 0;
}

/* HDU 4291 A Short problem
 *
 * Find:
 * g(g(g(n))) mod 109 + 7
 *
 * g(n) = 3g(n - 1) + g(n - 2)
 * g(1) = 1
 * g(0) = 0
 * 本地暴力打表找每层循环节
 * */
#include <cstdio>
#include <cstring>

typedef long long int64;

struct Matrix {
	int64 mt[2][2];
	void init_0() { memset(mt, 0, sizeof(mt));}
	void init(int v) { init_0(); for (int i = 0; i < 2; ++i) mt[i][i] = v; }
	Matrix() {init_0();}
	Matrix(int v) { init_0(); for (int i = 0; i < 2; ++i) mt[i][i] = v; }
	Matrix(int64 Mt[][2]) {
		for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) mt[i][j] = Mt[i][j];
	}
	Matrix mul(const Matrix &b, int64 mod) {
		Matrix r;
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 2; ++k) {
					r.mt[i][j] = (r.mt[i][j] + mt[i][k] * b.mt[k][j]) % mod;
				}
			}
		}
		return r;
	}
	Matrix qpow(int64 n, int64 mod) {
		Matrix res(1);
		if (n == 0) return res;
		if (n == 1) return *this;
		Matrix b = *this;
		while (n > 1) {
			if (n & 1) res = res.mul(b, mod);
			b = b.mul(b, mod);
			n >>= 1;
		}
		return b.mul(res, mod);
	}
};

int64 cal(int64 n, int64 mod) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	int64 m[2][2] = {{3, 1}, {1, 0}};
	Matrix mm(m), ori;
	ori.mt[0][0] = 1;
	return mm.qpow(n-1, mod).mul(ori, mod).mt[0][0];
}


int main() {
	int64 n;
	while (EOF != scanf("%lld", &n)) {
		printf("%lld\n", cal(cal(cal(n, 183120), 222222224), 1000000007));
	}
	return 0;
}

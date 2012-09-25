/* C. Flying Saucer Segments
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

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
					r.mt[i][j] = (r.mt[i][j] + mt[i][k] * b.mt[k][j]);
					if (r.mt[i][j] < 0) {
						r.mt[i][j] += ((-r.mt[i][j]) / mod  + 1) * mod;
					}
					r.mt[i][j] %= mod;
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
	if (n == 1) return 2 % mod;
	if (n == 2) return 8 % mod;
	int64 m[2][2] = {{4, -3}, {1, 0}};
	Matrix mm(m), ori;
	ori.mt[0][0] = 8 % mod;
	ori.mt[1][0] = 2 % mod;
	return mm.qpow(n-2, mod).mul(ori, mod).mt[0][0];
}


int main() {
	int64 n, m;
	while (cin >> n >> m) {
		cout << cal(n, m) << endl;
	}
	return 0;
}

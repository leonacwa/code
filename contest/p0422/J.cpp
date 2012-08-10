#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MR = 2;
const int MC = 2;
const int MOD = 1000000007;

typedef long long Matrix[MR][MC];
const Matrix A = {{2, 3}, {1, 0}};

void multi_mat(Matrix ia, Matrix ib, Matrix c)
{
	Matrix a, b;
	memcpy(a, ia, sizeof(Matrix));
	memcpy(b, ib, sizeof(Matrix));
	for (int i = 0; i < MR; ++i) {
		for (int j = 0; j < MC; ++j) {
			c[i][j] = 0;
			for (int k = 0; k < MC; ++k) {
				c[i][j] += a[i][k] * b[k][j] % MOD;
				c[i][j] %= MOD;
			}
		}
	}
}

void pow_mat(Matrix mat, int n)
{
	if (n == 0) {
		memset(mat, 0, sizeof(Matrix));
		for (int i = 0; i < MR; ++i) {
			mat[i][i] = 1;
		}
		return;
	}
	if (n == 1) {
		return;
	}
	Matrix mat2;
	memcpy(mat2, mat, sizeof(Matrix));
	pow_mat(mat, n / 2);
	multi_mat(mat, mat, mat);
	if (n % 2 == 1) {
		multi_mat(mat, mat2, mat);
	}
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n;
		scanf("%d", &n);
		Matrix res;
		memcpy(res, A, sizeof(Matrix));
		pow_mat(res, n - 1);
		long long g[2] = {0, 1};
		long long f = 3 * (g[1] * res[1][0] + g[0] * res[1][1]) % MOD;
		//printf("%lld %lld\n", res[1][0], res[1][1]);
		printf("%lld\n", f);
	}
	return 0;
}


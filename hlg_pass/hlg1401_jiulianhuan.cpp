#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MOD = 10007;
const int W = 3;
const int Raw[W][W] = {{1, 2, 1}, {1, 0, 0}, {0, 0, 1}};
const int Init[W][W] = {{2, 0, 0}, {1, 0, 0}, {1, 0, 0}};
int A[W][W], B[W][W];

void mat_mult(int A[W][W], int B[W][W], int C[W][W])
{
	int tC[W][W];
	for (int i = 0; i < W; ++i) {
		for (int j = 0; j < W; ++j) {
			tC[i][j] = 0;
			for (int k = 0; k < W; ++k) {
				tC[i][j] += A[i][k] * B[k][j];
				tC[i][j] %= MOD;
			}
		}
	}
	memcpy(C, tC, sizeof(tC[0][0]) * W * W);
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		int ans = n;
		if (n > 2) {
			memcpy(A, Raw, sizeof(Raw[0][0]) * W * W);
			memcpy(B, Init, sizeof(Init[0][0]) * W * W);
			n -= 2;
			while (n) {
				if (n & 1) {
					mat_mult(A, B, B);
				}
				mat_mult(A, A, A);
				n >>= 1;
			}
			ans = B[0][0];
		}
		printf("%d\n", ans);
	}
	return 0;
}


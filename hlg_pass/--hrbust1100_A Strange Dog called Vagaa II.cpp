#include <iostream>
using namespace std;
typedef long long llong;
llong tmp[3][3];
const llong MOD = 10007;
void mult(llong a[][3], llong b[][3], int x, int y, int z) {
	int i, j, k;
	for (i = 0; i < x; i++) {
		for (j = 0; j < z; j++) {
			tmp[i][j] = 0;
			for (k = 0; k < y; k++) {
				tmp[i][j] += a[i][k] * b[k][j];
				tmp[i][j] %= MOD;
			}
		}
	}
	for (i = 0; i < x; i++) for (j = 0; j < z; j++) a[i][j] = tmp[i][j];
}
int main() {
	//freopen("1063.in", "r", stdin);
	//freopen("1063.out", "w", stdout);
	int k, f;
	scanf("%d", &f);
	while (f--) {
		scanf("%d", &k);
		llong A[1][3] = {1, 0, 1}, B[3][3] = {{1, 1, 1}, {1, 0, 1}, {0, 0, 1}};
		while (k) {
			if (k & 1) mult(A, B, 1, 3, 3);
			mult(B, B, 3, 3, 3);
			k >>= 1;
		}
		printf("%lld\n", A[0][2]);
	}
}


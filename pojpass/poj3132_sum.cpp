#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
const int NN = 2000;
const int MM = 15;

int prm_cnt, prm[NN];
bool is[NN];
int f[MM][NN];

void getprm()
{
	memset(is, true, sizeof(is));
	is[0] = is[1] = false;
	int sn = int(sqrt(1.0 * NN));
	for (int i = 2; i <= sn; ++i) {
		for (int j = i + i; j <= NN; j += i) {
			is[j] = false;
		}
	}
	prm_cnt = 0;
	for (int i = 2; i <= NN; ++i) {
		if (is[i]) {
			prm[prm_cnt++] = i;
		}
	}
}

int main()
{
	getprm();
	int n, k;
	while (EOF != scanf("%d %d", &n, &k) && n > 0 && k > 0) {
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for (int h = 0; h < prm_cnt; ++h) {
			if (prm[h] > n) break;
			for (int i = k; i > 0; --i) {
				for (int j = n; j >= prm[h]; --j) {
					f[i][j] += f[i-1][j-prm[h]];
				}
			}
		}
		printf("%d\n", f[k][n]);
	}
	return 0;
}


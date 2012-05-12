#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
const int MAX_LEN = 1000;
const int NN = 41;

int len[NN];
bool f[2][MAX_LEN][MAX_LEN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &len[i]);
			sum += len[i];
		}
		memset(f, 0, sizeof(f));
		f[0][0][0] = true;
		int bound = sum / 2;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= bound; ++j) {
				for (int k = 0; k <= bound; ++k) {
					f[i % 2][j][k] = f[(i-1) % 2][j][k] 
						|| (j >= len[i] && f[(i-1) % 2][j-len[i]][k]) 
						|| (k >= len[i] && f[(i-1) % 2][j][k-len[i]]); 
				}
			}
		}
		int l = n % 2;
		double ans = 0;
		for (int a = 1; a <= bound; ++a) {
			for (int b = 1; b <= bound; ++b) {
				if (!f[l][a][b]) continue;
				int c = sum - a - b;
				if (!(a + b > c && abs(a - b) < c)) continue;
				double p = (a + b + c) / 2.0;
				double t = sqrt(p * (p - a) * (p - b) * (p - c));
				if(ans < t) {
					ans = t;
				}
			}
		}
		if (ans == 0.0) {
			puts("-1");
		} else {
			printf("%d\n", (int)(ans * 100));
		}
	}
	return 0;
}


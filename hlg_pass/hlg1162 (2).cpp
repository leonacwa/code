#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int n;
int pk[128][128];
int mt[128][128];
int a[128];

int main()
{
	while (EOF != scanf("%d", &n)) {
		memset(mt, -1, sizeof(mt));
		for (int i = 0; i < n; ++i) {
		   for (int j = 0; j < n; ++j) {
			scanf("%d", &pk[i][j]);
		   }
		}
		memset(mt, 0, sizeof(mt));
		for (int i = 0; i < n; ++i) {
			mt[i][(i+1) % n] = 1;
		}
		for (int l = 2; l <= n; ++l) {
			for (int i = 0; i < n; ++i) {
				int j = (i+l) % n;
				for (int k = (i+1) % n; k != j; k = (k+1) % n) {
					if (mt[i][k] && mt[k][j] && (pk[i][k] || pk[j][k])) {
						mt[i][j] = 1;
					}
				}
			}
		}
		int cnt = 0;
		for (int i = 0 ; i < n; ++i) {
			if (mt[i][i]) {
				a[cnt++] = i+1;
			}
		}
		printf("%d\n", cnt);
		for (int i= 0 ; i < cnt; ++i) {
			printf("%d\n", a[i]);
		}
	}
	return 0;
}


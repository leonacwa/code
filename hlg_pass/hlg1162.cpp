#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int n;
int pk[128][128];
int mt[128][128];
int a[128];
int meet(int i, int j)
{
	if (-1 != mt[i][j])
		return mt[i][j];
	if ((i+1)%n == j) {
		return mt[i][j] = 1;
	}
	for (int k = (i+1)%n; k != j; k = (k+1)%n) {
		if (meet(i, k) && meet(k, j) && (pk[i][k] || pk[j][k])) {
			return mt[i][j] = 1;
		}
	}
	return mt[i][j] = 0;
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		memset(mt, -1, sizeof(mt));
		for (int i = 0; i < n; ++i) {
		   for (int j = 0; j < n; ++j) {
			scanf("%d", &pk[i][j]);
		   }
		}
		int cnt = 0;
		for (int i = 0 ; i < n; ++i) {
			if (meet(i, i)) {
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


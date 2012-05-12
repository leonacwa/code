#include <stdio.h>
#include <string.h>
const int NN = 1005;
int l1, l2;
char s1[NN], s2[NN];
int f[NN][NN];

int main()
{
	while (EOF != scanf("%d %s", &l1, s1+1)) {
		scanf("%d %s", &l2, s2+1);
		for (int i = 0; i <= l1; ++i) f[i][0] = i;
		for (int i = 0; i <= l2; ++i) f[0][i] = i;
		for (int i = 1; i <= l1; ++i) {
			for (int j = 1; j <= l2; ++j) {
				f[i][j] = f[i-1][j] + 1;
				if (f[i][j] > f[i][j-1] + 1) {
					f[i][j] = f[i][j-1] + 1;
				}
				if (f[i][j] > f[i-1][j-1] + (s1[i] != s2[j])) {
					f[i][j] = f[i-1][j-1] + (s1[i] != s2[j]);
				}
			}
		}
		printf("%d\n",f[l1][l2]);
	}
	return 0;
}


#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 200;
char s1[NN], s2[NN];
int f[NN][NN], opt[NN][NN];
char ans[NN*2];

int main()
{
	while (EOF != scanf("%s %s", s1+1, s2+1)) {
		int l1 = strlen(s1+1), l2 = strlen(s2+1);
		f[0][0] = 0;
		opt[0][0] = 0;
		for (int i = 1; i <= l1; ++i) {
			f[i][0] = 0;
			opt[i][0] = 2;
		}
		for (int i = 1; i <= l2; ++i) {
			f[0][i] = 0;
			opt[0][i] = 3;
		}
		for (int i = 1; i <= l1; ++i) {
			for (int j = 1; j <= l2; ++j) {
				f[i][j] = -1;
				opt[i][j] = 0;
				if (s1[i] == s2[j]) {
					f[i][j] = f[i-1][j-1] + 1;
					opt[i][j] = 1;
				}
				if (f[i][j] < f[i-1][j]) {
					f[i][j] = f[i-1][j];
					opt[i][j] = 2;
				}
				if (f[i][j] < f[i][j-1]) {
					f[i][j] = f[i][j-1];
					opt[i][j] = 3;
				}
			}
		}
		int len = l1 + l2 - f[l1][l2];
		ans[len] = 0;
		int i = l1, j = l2;
		for (int l = len-1; l >= 0; --l) {
			if (opt[i][j] == 1) {
				ans[l] = s1[i];
				--i, --j;
			} else if (opt[i][j] == 2) {
				ans[l] = s1[i];
				--i;
			} else if (opt[i][j] == 3) {
				ans[l] = s2[j];
				--j;
			} else {
				break;
			}
		}
		puts(ans);
	}
	return 0;
}


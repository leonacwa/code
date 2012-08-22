#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
const int NN = 1000000 + 10;
bool mark[NN];
char ans[NN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n) && n > 0) {
		int n10 = int(pow(10.0, 1. * n) + 0.000001);
		int nmod = n10 / 10;
		int len = n10 + n - 1;
		memset(mark, 0, sizeof(mark[0]) * (n10 + 1));
		int l = 0;
		for (l = 0; l < n; ++l) {
			ans[l] = '0';
		}
		int v = 0, i = 0;;
		mark[v] = true;
		while (l < len) {
			v = v % nmod;
			for (; i < 10; ++i) {
				int t = v * 10 + i;
				if (!mark[t]) {
					v = t;
					mark[v] = true;
					ans[l++] = i + '0';
					i = 0;
					break;
				}
			}
			if (i == 10 && l < len) {
				v = (ans[l - n] - '0') * nmod + v;
				--l;
				mark[v] = false;
				i = ans[l] - '0' + 1;
				v /= 10;
			}
		}
		ans[l] = 0;
		puts(ans);
	}
	return 0;
}


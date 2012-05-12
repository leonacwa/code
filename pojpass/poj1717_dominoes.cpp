#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;
const int S = 6000;
const int N = 1005;

int f[2][2*S+5];
int dt[N];
int n;

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			dt[i] = a - b;
		}
		for (int i = 0; i <= 2*S; ++i) {
			f[0][i] = INT_MAX;
		}
		f[0][S+dt[0]] = 0;
		f[0][S-dt[0]] = 1;
		for (int i = 1; i < n; ++i) {
			for (int j = -S; j <= S; ++j) {
				f[i % 2][S+j] = f[(i-1) % 2][S + j - dt[i]];
				if (f[(i-1) % 2][S + j + dt[i]] < INT_MAX) {
					f[i % 2][S+j] = min(f[i % 2][S+j], f[(i-1) % 2][S + j + dt[i]] + 1);
				}
			}
		}
		int diff = 0, ans =  INT_MAX, l = (n-1) % 2;
		while (ans == INT_MAX) {
			ans = min(f[l][S+diff], f[l][S-diff]);
			++diff;
		}
		printf("%d\n", ans);
	}
	return 0;
}


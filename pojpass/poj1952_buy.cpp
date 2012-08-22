#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 5003;

int n;
int a[NN];
int f[NN];
long long cnt[NN];

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", a+i);
		}
		a[n] = -1;
		f[0] = 1;
		cnt[0] = 1;
		int t = -1;
		for (int i = 1; i <= n; ++i) {
			f[i] = 1;
			cnt[i] = 1;
			for (int j = i - 1; j >= 0; --j) {
				if (a[j] > a[i]) {
					if (f[i] < f[j] + 1) {
						f[i] = f[j] + 1;
						cnt[i] = cnt[j];
						t = a[j];
					} else if (f[i] == f[j] + 1 && t != a[j]) {
						cnt[i] += cnt[j];
						t = a[j];
					}
				}
			}
		}
		printf("%d %lld\n", f[n]-1, cnt[n]);
	}
	return 0;
}


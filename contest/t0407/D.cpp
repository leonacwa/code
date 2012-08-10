#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n, m;
int p[50];
int f[1005];
int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		scanf("%d", &m);
		int max = -100, mp = -1;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &p[i]);
			if (max < p[i]) {
				max = p[i];
				mp = i;
			}
		}
		if (m < 5) {
			printf("%d\n", m);
			continue;
		}
		p[mp] = p[n-1];
		m -= 5;
		memset(f, 0, sizeof(f));
		for (int i = 0; i < n-1; ++i) {
			for (int j = m; j >= p[i]; --j) {
				if (f[j] < f[j-p[i]] + p[i]) {
					f[j] = f[j-p[i]] + p[i];
				}
			}
		}
		printf("%d\n", m + 5 - f[m] - max);
	}
	return 0;
}


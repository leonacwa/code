#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 15;
const int VV = 1000 + 10;

int maxans, ans_cnt, ans[NN];
int d[NN];
bool f[NN][VV];
bool in[VV];

int main()
{
	int s;
	while (EOF != scanf("%d", &s) && s > 0) {
		int m;
		scanf("%d", &m);
		maxans = -1;
		ans_cnt = 0;
		while (m--) {
			int n;
			scanf("%d", &n);
			for (int i = 0; i < n; ++i) {
				scanf("%d", &d[i]);
			}
			int maxv = d[n-1] * s;
			if (maxv < maxans) continue;
			memset(f, 0, sizeof(f));
			memset(in, 0, sizeof(in));
			f[0][0] = true;
			in[0] = true;
			for (int i = 0; i < n; ++i) {
				for (int j = 1; j <= s; ++j) {
					for (int k = d[i]; k <= maxv; ++k) {
						if (f[j-1][k - d[i]]) {
							f[j][k] = true;
							in[k] = true;
						}
					}
				}
			}
			int b = 0;
			for (b = 1; b <= maxv && in[b]; ++b) {
			}
			--b;
			if (b > maxans || (b == maxans && (n < ans_cnt || (n == ans_cnt && d[n-1] < ans[ans_cnt-1])))) {
				maxans = b;
				ans_cnt = n;
				for (int i = 0; i < n; ++i) {
					ans[i] = d[i];
				}
			}
		}
		printf("max coverage = %d :", maxans);
		for (int i = 0; i < ans_cnt; ++i) {
			printf(" %d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}


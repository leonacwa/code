#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

int n, c1, c2;
int w[100];
int stat_cnt;
int stat[1 << 10];
bool f[101];
int ff[1 << 10];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	for (int nCase = 1; nCase <= nTest; ++nCase) {
		scanf("%d %d %d", &n, &c1, &c2);
		if (c1 > c2) {
			swap(c1, c2);
		}
		for (int i = 0; i < n; ++i) {
			scanf("%d", w+i);
		}
		stat_cnt = 1;
		stat[0] = 0;
		for (int s = (1 << n) - 1; s >= 0; --s) {
			int sum = 0;
			memset(f, 0, sizeof(f));
			f[0] = true;
			for (int i = 0; i < n; ++i) {
				if (!(s & (1 << i))) continue;
				sum += w[i];
				for (int j = c1; j >= w[i]; --j) {
					f[j] = f[j] || f[j - w[i]];
				}
			}
			for (int i = c1; i >= 0; --i) {
				if (f[i] && sum - i <= c2) {
					stat[stat_cnt++] = s;
					break;
				}
			}
		}
		for (int i = (1 << n) - 1; i >= 0; --i) {
			ff[i] = INT_MAX;
		}
		ff[0] = 0;
		for (int i = 0; i < stat_cnt; ++i) {
			int s = stat[i];
			ff[s] = 1;
			for (int j = (1 << n) - 1; j >= 0; --j) {
				if (j & s) continue;
				if (ff[j] < INT_MAX && ff[j | s] > ff[j] + 1) {
					ff[j | s] = ff[j] + 1;
				}
			}
		}
		printf("Scenario #%d:\n%d\n\n", nCase, ff[(1 << n)-1]);
	}
	return 0;
}


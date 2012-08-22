#include <stdio.h>
#include <string.h>

const int NN = 18;
const int MAXSS = 1 << NN;
int st[MAXSS];
int st_cnt[MAXSS];
int value[MAXSS];
int nSt;
int f[1<<NN];
int n, k;
int A[NN];

void init()
{
	int end = 1 << NN;
	nSt = 0;
	for (int i = 0; i < end; ++i) {
		int cnt = 0;
		for (int d = i; d; d >>= 1) {
			cnt += d & 1;
		}
		if (cnt > 0 && cnt % 3 == 0) {
			st_cnt[nSt] = cnt;
			st[nSt++] = i;
		}
	}
}

int main()
{
	int nCase;
	init();
	scanf("%d", &nCase);
	while (nCase--) {
		scanf("%d %d", &k, &n);
		for (int i = 0; i < n; ++i) {
		   	scanf("%d", &A[i]);
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int t;
				scanf("%d", &t);
				value[(1 << i) | (1 << j)] = 2 * t + A[i] + A[j];
			}
		}
		memset(f, 0, sizeof(f));
		int ans = 0;
		int end = 1 << n;
		for (int i = 1; i < nSt; ++i) {
			if (st_cnt[i] > 3*k ) continue;
			int s = st[i];
			if (s >= end) break;
			int b0 = s & -s;
			int s1 = s ^ b0;
			while (s1) {
				int b1 = s1 & -s1;
				s1 ^= b1;
				int s2 = s1;
				while (s2) {
					int b2 = s2 & -s2;
					s2 ^= b2;
					int t = value[b0 | b1] + value[b0 | b2] + value[b1 | b2] + f[s ^ b0 ^ b1 ^ b2];
					if (f[s] < t) {
						f[s] = t;
					}
				}
			}
			if (ans < f[s]) ans = f[s];
		}
		printf("%d\n", ans / 2);
	}
	return 0;
}


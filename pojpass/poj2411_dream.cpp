#include <stdio.h>
#include <string.h>

const int NN = 11;

int S[1 << NN];
int S_cnt;
long long F[NN][1 << NN];
/*
 * F[i][k]表示第i行能产生的凹凸状态
 * S[]记录的是一行都要放置方块时的合法凹凸状态
 * 对于第i-1行产生的凹凸状态不能使得第i行进行都放置的状态si,则在si对于那些使得凹凸位置为1的位置，可以使用si-1对应位置为1的放置，产生新的状态si'，并且si'对应位的凹凸状态由1变为0
 * */
void init(int n)
{
	S_cnt = 0;
	for (int s = (1 << n) - 1; s >= 0; --s) {
		int p = 0;
		bool can = true;
		while (p < n && can) {
			if (s & (1 << p)) {
				++p;
			} else {
				if (n > p+1 && !(s & (1 << (p+1)))) {
					p += 2;
				} else {
					can = false;
				}
			}
		}
		if (can) {
			S[S_cnt++] = s;
		}
	}
}

int main()
{
	int h, w;
	while (EOF != scanf("%d %d", &h, &w) && h > 0 && w > 0) {
		init(w);
		memset(F, 0, sizeof(F));
		for (int i = 0; i < S_cnt; ++i) {
			F[0][S[i]] = 1;
		}
		for (int i = 1; i < h; ++i) {
			for (int j = 0; j < S_cnt; ++j) {
				for (int k = (1 << NN) -1; k >= 0; --k) {
					if ((S[j] & k) != k) continue;
					F[i][S[j] ^ k] += F[i-1][k];
				}
			}
		}
		//printf("%lld\n", F[h-1][0]); // for linux
		printf("%I64d\n", F[h-1][0]); // for windows
	}
	return 0;
}


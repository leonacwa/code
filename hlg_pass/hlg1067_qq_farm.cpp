#include <stdio.h>
#include <string.h>

const double eps = 1e-8;
const int MAXN = 10;
double X[MAXN], Y[MAXN];
double R;
int N, T;
int ret[1<<MAXN];
int ret_cnt;
int sz[1<<MAXN];
int dp[2][1<<MAXN];

void init()
{
	memset(ret, 0, sizeof(ret));
	ret_cnt = 0;
	bool used[1<<MAXN] = {false};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int rec = 0;
			for (int k = 0; k < N; k++) {
				if ((X[i] <= X[k]+eps && X[k]-eps <= X[i]+R) && (Y[j] <= Y[k]+eps && Y[k]-eps <= Y[j]+R)) {
					rec |= (1 << k);
				}
			}
			if (false == used[rec]) {
				ret[ret_cnt++] = rec;
				used[rec] = true;
			}
			rec = 0;
			for (int k = 0; k < N; k++) {
				if ((X[i]-R <= X[k]+eps && X[k]-eps <= X[i]) && (Y[j]-R <= Y[k]+eps && Y[k]-eps <= Y[j])) {
					rec |= (1 << k);
				}
			}
			if (false == used[rec]) {
				ret[ret_cnt++] = rec;
				used[rec] = true;
			}
		}
	}	
}

int main()
{
	for (int i = 0; i < (1<<MAXN); i++) {
		sz[i] = 0;
		int j = i;
		while (j) {
			sz[i]++;
			j -= (-j)&j;
		}
	}
	while (EOF != scanf("%d %d", &N, &T)) {
		int l = 0;
		memset(dp, 0, sizeof(dp));
		scanf("%lf", &R);
		for (int i = 0; i < T; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%lf %lf", &X[j], &Y[j]);
			}
			init();
			l = i  % 2;
			memset(dp[l], 0x81, sizeof(dp[l]));
			for (int i = 0; i < ret_cnt; i++) {
				for (int j = 0; j < (1<<N); j++) {
					if (dp[1-l][j] >= 0) {
						int st = (ret[i]&j)^ret[i];
						if (st > 0) {
							if (dp[l][ret[i] | j] < dp[1-l][j] + sz[st]*sz[st]) {
								dp[l][ret[i] | j] = dp[1-l][j] + sz[st]*sz[st];
							}
						}
					}
				}
			}
		}
		l = (T-1) % 2;
		int ans = 0;
		for (int i = 0; i < (1<<N); i++) {
			if (ans < dp[l][i]) {
				ans = dp[l][i];
			}
		}	
		printf("%d\n", ans);
	}
	return 0;
}


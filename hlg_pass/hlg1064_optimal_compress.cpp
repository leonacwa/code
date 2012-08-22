#include <stdio.h>
#include <string.h>

const int MAXN = 201;
const int INF = 9999999;

char str[256];
struct Ve {
	int e[MAXN];
	int cnt;
};
Ve adj[MAXN][MAXN]; // adjacent parts, adj[i][len].[k] = j, => str[i..i+len-1] == str[j..j+len-1]
int lcp[MAXN][MAXN]; // longest common parts, lcp[i][j] = len, str[i..i+len-1] == str[j..j+len-1]
int dps[MAXN][MAXN][MAXN]; //

inline int min(int a, int b) { 
	return a<b?a:b;
}

int dp(int l, int r, int len)
{
	if (l == r) {
		if (len > 0) {
			if (len == 1) {
				return 4;
			}
			return INF;
		}
		return 1;
	}
	if (l > r) {
		if (len == 0) {
			return 0;
		}
		return INF;
	}
	if (dps[l][r][len] != -1) {
		return dps[l][r][len];
	}
	if (len == 0) {
		dps[l][r][len] = r - l + 1;
		for (int i = l; i < r; i++) {
			dps[l][r][len] = min(dps[l][r][len], dp(l, i, 0) + dp(i+1, r, 0));
		}
		int half = (r-l+1) / 2;
		for (int i = 1; i <= half; i++) {
			if (lcp[l][r-i+1] >= i) { // optimal 
				dps[l][r][len] = min(dps[l][r][len], dp(l, r, i));
			}
		}
	} else {
		dps[l][r][len] = dp(l, l+len-1, 0) + 3 + dp(l+len, r, 0);
		for (int i = 0; i < adj[l][len].cnt; i++) {
			if (l+len == adj[l][len].e[i]) {
				dps[l][r][len] = min(dps[l][r][len], dp(l+len, r, len));
			} else {
				dps[l][r][len] = min(dps[l][r][len], dp(l+len, adj[l][len].e[i]-1, 0) + 3 + dp(adj[l][len].e[i], r, len));
			}
		}
	}
	return dps[l][r][len];
}

int main()
{
	while (EOF != scanf("%s", str) && str[0] != '*') {
		memset(lcp, 0, sizeof(lcp));
		int len = strlen(str);
		for (int i = 0; i < len; i++) {
			for (int j = i+1; j < len; j++) {
				int k = 1;
				for (k = 1; j+k-1 < len && str[i+k-1] == str[j+k-1]; k++) {
				}
				lcp[i][j] = k - 1;
			}
		}
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < len; i++) {
			for (int j = i+1; j < len; j++) {
				for (int l = 1; l <= j-i && l <= lcp[i][j]; l++) {
					adj[i][l].e[adj[i][l].cnt++] = j;
				}
			}
		}
		memset(dps, 0xff, sizeof(dps));
		printf("%d\n", dp(0, len-1, 0));
	}
	return 0;
}


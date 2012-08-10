#include <stdio.h>
#include <string.h>

const int LV = 76;
int w[26] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1};
char s[26][32];
char pre[26];
int ans;

int ci(char c) {return c - 'A';}

void dfs(int c, int dp[])
{
	int dp2[LV+1];
	memset(dp, 0, sizeof(dp[0]) * (LV+1));
	for (int i = 1; s[c][i]; ++i) {
		dfs(ci(s[c][i]), dp2);
		for (int v1 = LV; v1 >= w[c]+1; --v1) {
			if (dp[v1] > 0) {
				for (int v2 = 1; v1 + v2 <= LV; ++v2) {
					dp[v1+v2] += dp[v1] * dp2[v2];
				}
			}
		}
		for (int v1 = 1; v1 <= LV-w[c]; ++v1) {
			dp[v1+w[c]] += dp2[v1];
		}
	}
	dp[w[c]] = 1;
	dp[0] = 1;
	ans += dp[25];
}

int main()
{
	int nTest;
	char str[32];
	int dp[LV+1];
	scanf("%d", &nTest);
	while (nTest--) {
		memset(pre, 0, sizeof(pre));
		memset(s, 0, sizeof(s));
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%s", str);
			for (char *ptr = str + 1; *ptr; ++ptr) {
				pre[ci(*ptr)] = str[0];
			}
			strcpy(s[ci(str[0])], str);
		}
		ans = 0;
		for (int i = 0; i < 26; ++i) {
			if (s[i][0] && pre[s[i][0]] == '\0') {
				memset(dp, 0, sizeof(dp));
				dfs(ci(s[i][0]), dp);
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


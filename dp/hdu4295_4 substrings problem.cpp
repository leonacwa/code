/* HDU 4295 4 substrings problem
 * 非常值得做的DP题
 * From:http://www.cnblogs.com/staginner/archive/2012/09/18/2691677.html
 * 可以用f[i][j][k]表示递推到S的第i个字符时，选取的字符串的集合为k（用二进制表示），从当前字符开始向后已经覆盖了长度j的字符。
 * 在这里不妨只讨论最小覆盖长度，最大覆盖长度类似。为了方便dp所以选用刷表的方式，首先令f[i][0][0]为0，接着对于任意一个f[i][j][k]，实际上有两种决策，一种是当前这个位置什么也不放就过度到下一个字符，那么就有f[i+1][j-1][k]=std::min(f[i+1][j-1][k],f[i][j][k])，另一种就是从当前位置开始放上字符串t，这时要稍稍讨论一下，因为字符串t的长度可能会影响状态j，也就是从当前字符开始向后已经覆盖了的长度，设放上字符串t后的j的状态为nj，f的值nf，那么就有f[i][nj][k|1<<t]=std::min(f[i][nj][k|1<<t],nf)
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 0x3fffffff;
const int MAXN = 4100;
char str[MAXN];
int can[MAXN];
int len[16], lb[4];
int f[MAXN][16][65];

int dp(int ls, int INF, const int &(&cmp)(const int&, const int&)) {
	for (int i = 0; i <= ls; ++i) {
		for (int j = 0; j < 16; ++j) {
			for (int k = 0; k <= 64; ++k) f[i][j][k] = INF;
		}
	}
	f[0][0][0] = 0;
	for (int i = 0; i < ls; ++i) {
		for (int j = 0; j < 16; ++j) {
			for (int k = 0; k <= 64; ++k) {
				if (f[i][j][k] == INF) continue;
				int nk = max(0, k-1);
				/* i+1位置不重新覆盖，用之前的继续覆盖 */
				f[i+1][j][nk] = cmp(f[i+1][j][nk], f[i][j][k]);
				int cur = (15^j) & can[i];
				for (int s = cur; s; s = (s-1)&cur) { /* i 位置再加上其它字符串一起覆盖 */
					nk = max(k, len[s]);
					f[i][j|s][nk] = cmp(f[i][j|s][nk], f[i][j][k] + max(0, len[s] - k));
				}
			}
		}
	}
	return f[ls][15][0];
}

int main() {
	while (EOF != scanf("%s", str)) {
		int ls = strlen(str);
		memset(can, 0, sizeof(can));
		for (int k = 0; k < 4; ++k) {
			char s[65];
			scanf("%s", s);
			lb[k] = strlen(s);
			for (int i = 0; i < ls; ++i) {
				bool pd = true;
				for (int j = 0; j < lb[k]; ++j) {
					if (i+j >= ls || s[j] != str[i+j]) {
						pd = false;
						break;
					}
				}
				if (pd) can[i] |= 1<<k;
			}
		}
		memset(len, 0, sizeof(len));
		for (int s = 1; s < 16; ++s) {
			for (int i = 0; i < 4; ++i) {
				if (s & (1<<i)) len[s] = max(len[s], lb[i]);
			}
		}
		int ans1 = dp(ls, INF, min), ans2 = dp(ls, -INF, max);
		printf("%d %d\n", ans1, ans2);
	}
	return 0;
}
